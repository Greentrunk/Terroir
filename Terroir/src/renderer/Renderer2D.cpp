////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Christopher J. Pohl 2023 to Present  All Rights Reserved.
//
// This file is part of TERROIR ENGINE:
// This is free software as described by the Apache 2.0 License
//
// The above copyright notice shall be included in all portions of this software
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#include "Renderer2D.h"
#include "RenderCommand.h"
#include "Tpch.h"
#include "VertexArray.h"

namespace Terroir
{

static std::unique_ptr<Renderer2DData> s_Data;

void Renderer2D::Init()
{
    // New data
    s_Data = std::make_unique<Renderer2DData>();
    TERR_PROFILE_ALLOC_SMART(s_Data);

    // Temp
    std::array<f32, 5 * 4> vertices{-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,
                                    0.5f,  0.5f,  0.0f, 1.0f, 1.0f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f};
    std::array<u32, 6> indices{0, 1, 2, 2, 3, 0};

    s_Data->m_QUAD_VAO = VertexArray::Create();
    s_Data->m_QUAD_VBO = VertexBuffer::Create(&vertices[0], sizeof(vertices));

    BufferLayout layout{{"a_Position", ShaderDataType::Vec3}, {"a_TexCoord", ShaderDataType::Vec2}};
    s_Data->m_QUAD_VBO->SetLayout(layout);
    s_Data->m_QUAD_VAO->AddVertexBuffer(s_Data->m_QUAD_VBO);

    s_Data->m_QUAD_IBO = IndexBuffer::Create(&indices[0], static_cast<u32>(indices.size()));
    s_Data->m_QUAD_VAO->SetIndexBuffer(s_Data->m_QUAD_IBO);

    s_Data->m_WhiteTexture = Texture2D::Create(1, 1);
    auto whiteTextureData{0xffffffff};
    s_Data->m_WhiteTexture->SetData(&whiteTextureData, sizeof(whiteTextureData));

    s_Data->m_QUAD_VBO->Unbind();
    s_Data->m_QUAD_VAO->Unbind();

    s_Data->m_TextureShader = Shader::Create("Texture", {"Terroir/src/renderer/shader/TextureVertexShader.glsl",
                                                         "Terroir/src/renderer/shader/TextureFragShader.glsl"});
    s_Data->m_TextureShader->Bind();
    s_Data->m_TextureShader->SetUniform("u_Texture", 0);
}

void Renderer2D::BeginScene(const OrthographicCamera &camera)
{
    s_Data->m_TextureShader->Bind();
    s_Data->m_TextureShader->SetUniform("u_ViewProjection", camera.GetViewProjectionMatrix());
}

void Renderer2D::DrawRect(const Vec2 &pos, const Vec2 &size, const Vec4 &color, f32 rotation)
{
    DrawRect({pos.x, pos.y, 0.0f}, size, color, rotation);
}

void Renderer2D::DrawRect(const Vec3 &pos, const Vec2 &size, const Vec4 &color, f32 rotation)
{
    s_Data->m_TextureShader->SetUniform("u_Color", color);
    s_Data->m_WhiteTexture->Bind();

    const auto scale{Math::Transform::Scale(Mat4(1.0f), {size.x, size.y, 1.0f})};
    Mat4 rotate{1.0f};

    // Set rotation if default value isn't used
    if (rotation != 0.0f)
    {
        rotate = Math::Transform::Rotate(Mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f});
    }
    const auto transform{Math::Transform::Translate(Mat4(1.0f), pos) * scale * rotate};
    s_Data->m_TextureShader->SetUniform("u_Transform", transform);

    // Draw Indexed arrays
    s_Data->m_QUAD_VAO->Bind();
    RenderCommand::DrawIndexed(s_Data->m_QUAD_VAO);
}

void Renderer2D::DrawSprite(const Sprite &sprite)
{
    sprite.GetTexture()->Bind();

    s_Data->m_TextureShader->SetUniform("u_Color", sprite.GetTintColor());
    s_Data->m_TextureShader->SetUniform("u_TileFactor", sprite.GetTileFactor());

    s_Data->m_TextureShader->SetUniform("u_Transform", sprite.GetTransform());

    // Draw Indexed arrays
    s_Data->m_QUAD_VAO->Bind();
    RenderCommand::DrawIndexed(s_Data->m_QUAD_VAO);
}

// void Renderer2D::DrawSprite(const Vec2 &pos, const Vec2 &size, const std::shared_ptr<Texture2D> &texture, f32
// rotation,
//                           const Vec4 &tintColor, f32 tileFactor)
//{
//     DrawSprite({pos.x, pos.y, 0.0f}, size, texture, rotation, tintColor, tileFactor);
// }

void Renderer2D::EndScene()
{
}

void Renderer2D::Shutdown()
{
    s_Data.reset();
    TERR_PROFILE_FREE_SMART(s_Data);
}
Renderer2D::~Renderer2D()
{
    // Profile frees
}

} // namespace Terroir