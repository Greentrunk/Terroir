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
#include "Terroir/src/core/Color.h"
#include "Tpch.h"
#include "VertexArray.h"
#include <glad/glad.h>

namespace Terroir
{

static std::unique_ptr<Renderer2DData> s_Data;

void Renderer2D::Init()
{
    // New data
    s_Data = std::make_unique<Renderer2DData>();
    TERR_PROFILE_ALLOC_SMART(s_Data);

    s_Data->m_RECT_VAO = VertexArray::Create();
    s_Data->m_RECT_VBO = VertexBuffer::Create(s_Data->MAX_VERTICES * sizeof(RectVertex));

    BufferLayout layout{{"a_Position", ShaderDataType::Vec3},
                        {"a_Color", ShaderDataType::Vec4},
                        {"a_TexCoord", ShaderDataType::Vec2},
                        {"a_TexIndex", ShaderDataType::Float},
                        {"a_TilingFactor", ShaderDataType::Float}};

    s_Data->m_RECT_VBO->SetLayout(layout);
    s_Data->m_RECT_VAO->AddVertexBuffer(s_Data->m_RECT_VBO);

    s_Data->m_RectVertexBufferBase = std::make_shared<RectVertex[]>(s_Data->MAX_VERTICES);

    // Create indices
    auto rectIndices{std::make_unique<u32[]>(s_Data->MAX_INDICES)};
    auto offset{0};
    for (u32 i = 0; i < s_Data->MAX_INDICES; i += 6)
    {
        rectIndices[i + 0] = offset + 0;
        rectIndices[i + 1] = offset + 1;
        rectIndices[i + 2] = offset + 2;

        rectIndices[i + 3] = offset + 2;
        rectIndices[i + 4] = offset + 3;
        rectIndices[i + 5] = offset + 0;

        offset += 4;
    }

    s_Data->m_RECT_IBO = IndexBuffer::Create(rectIndices.get(), s_Data->MAX_INDICES);
    s_Data->m_RECT_VAO->SetIndexBuffer(s_Data->m_RECT_IBO);

    s_Data->m_WhiteTexture = Texture2D::Create(1, 1);
    auto whiteTextureData{0xffffffff};
    s_Data->m_WhiteTexture->SetData(&whiteTextureData, sizeof(whiteTextureData));

    s_Data->m_RECT_VBO->Unbind();
    s_Data->m_RECT_VAO->Unbind();

    // Setup sampler as a span of size MAX_TEXTURE_SLOTS
    const auto textureSlots = 32;
    auto samplers{std::array<i32, textureSlots>{}};
    for (auto i = 0; i < textureSlots; i++)
        samplers[i] = i;

    // Texture shader
    s_Data->m_ShaderLibrary.Load("Texture", {"Terroir/src/renderer/shader/TextureVertexShader.glsl",
                                             "Terroir/src/renderer/shader/TextureFragShader.glsl"});
    s_Data->m_ShaderLibrary.Get("Texture")->Bind();
    s_Data->m_ShaderLibrary.Get("Texture")->SetUniform("u_Textures", samplers);

    // Set texture slot 0 to white texture
    s_Data->m_TextureSlots[0] = s_Data->m_WhiteTexture;

    // Set RectVertexPositions
    s_Data->m_RectVertexPositions[0] = {-0.5f, -0.5f, 0.f, 1.0f};
    s_Data->m_RectVertexPositions[1] = {0.5f, -0.5f, 0.f, 1.0f};
    s_Data->m_RectVertexPositions[2] = {0.5f, 0.5f, 0.f, 1.0f};
    s_Data->m_RectVertexPositions[3] = {-0.5f, 0.5f, 0.f, 1.0f};

    // Font shader
    s_Data->m_ShaderLibrary.Load("Font", {"Terroir/src/renderer/shader/FontVertexShader.glsl",
                                          "Terroir/src/renderer/shader/FontFragShader.glsl"});

    s_Data->m_Font = std::make_shared<Font>();

    // configure VAO/VBO for font texture quads
    s_Data->m_fVAO = VertexArray::Create();
    // base empty array for font vertex buffer
    std::array<f32, 6 * 4> fvertices{0.f};
    s_Data->m_fVBO = VertexBuffer::Create(fvertices.data(), sizeof(fvertices), true);

    BufferLayout fLayout{{"a_Vertex", ShaderDataType::Vec4}};
    s_Data->m_fVBO->SetLayout(fLayout);
    s_Data->m_fVAO->AddVertexBuffer(s_Data->m_fVBO);

    s_Data->m_fVAO->Unbind();
    s_Data->m_fVBO->Unbind();
}

void Renderer2D::BeginScene(const OrthographicCamera &camera)
{
    s_Data->m_ShaderLibrary.Get("Texture")->Bind();
    s_Data->m_ShaderLibrary.Get("Texture")->SetUniform("u_ViewProjection", camera.GetViewProjectionMatrix());
    s_Data->m_ShaderLibrary.Get("Font")->Bind();
    s_Data->m_ShaderLibrary.Get("Font")->SetUniform("u_ViewProjection", camera.GetViewProjectionMatrix());
    // unbind shaders
    s_Data->m_ShaderLibrary.Get("Texture")->Unbind();
    s_Data->m_ShaderLibrary.Get("Font")->Unbind();

    // Reset index count for batch
    s_Data->m_RectIndexCount = 0;
    // Set RectVertexBuffer to base
    s_Data->m_RectVertexBufferPtr = s_Data->m_RectVertexBufferBase.get();

    // Reset index count for texture slot
    s_Data->m_TextureSlotIndex = 1;
}

void Renderer2D::DrawRect(const Vec2 &pos, const Vec2 &size, const Vec4 &color, f32 rotation)
{
    DrawRect({pos.x, pos.y, 0.0f}, size, color, rotation);
}

void Renderer2D::DrawRect(const Vec3 &pos, const Vec2 &size, const Vec4 &color, f32 rotation)
{
    if (s_Data->m_RectIndexCount >= s_Data->MAX_INDICES)
    {
        FlushAndReset();
    }

    // Bind correct shader
    s_Data->m_ShaderLibrary.Get("Texture")->Bind();

    // White texture index
    constexpr const f32 texIndex{0.0f};
    constexpr const f32 tilingFactor{1.0f};

    // Transform - translate, rotate, scale
    const auto translate{Math::Transform::Translate(Mat4(1.0f), pos)};
    Mat4 rotate{1.0f};
    // Set rotation if default value isn't used
    if (rotation != 0.0f)
    {
        rotate = Math::Transform::Rotate(Mat4(1.0f), Math::Conversion::ToRadians(rotation), {0.0f, 0.0f, 1.0f});
    }

    const auto scale{Math::Transform::Scale(Mat4(1.0f), {size.x, size.y, 1.0f})};

    auto transform{translate * rotate * scale};
    auto texCoords{std::array<Vec2, 4>{{{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}}}};

    constexpr const auto rectVertexCount{4};

    SetRectVertexBufferData(transform, color, texCoords, texIndex, tilingFactor, rectVertexCount);

    s_Data->m_RectIndexCount += 6;

    s_Data->m_Stats.m_RectCount++;
}

void Renderer2D::DrawSprite(const Sprite &sprite)
{
    if (s_Data->m_RectIndexCount >= s_Data->MAX_INDICES)
    {
        FlushAndReset();
    }

    // Bind correct shader
    s_Data->m_ShaderLibrary.Get("Texture")->Bind();

    // Default color
    constexpr Vec4 color = Color::WHITE;

    auto texIndex{0.0f};

    // Check if texture is already in slot
    for (u32 i{1}; i < s_Data->m_TextureSlotIndex; i++)
    {
        // Check if textures are equal
        if (*s_Data->m_TextureSlots[i].get() == *sprite.GetTexture().get())
        {
            texIndex = static_cast<f32>(i);
            break;
        }
    }

    if (texIndex == 0.0f)
    {
        texIndex = static_cast<f32>(s_Data->m_TextureSlotIndex);
        s_Data->m_TextureSlots[s_Data->m_TextureSlotIndex] = sprite.GetTexture();
        s_Data->m_TextureSlotIndex++;
    }

    const auto transform{sprite.GetTransform()};
    const auto tilingFactor{sprite.GetTilingFactor()};
    const auto texCoords{sprite.GetTexCoords()};

    constexpr const auto rectVertexCount{4};

    SetRectVertexBufferData(transform, color, texCoords, texIndex, tilingFactor, rectVertexCount);

    s_Data->m_RectIndexCount += 6;

    s_Data->m_Stats.m_RectCount++;
}

void Renderer2D::DrawText(const std::string &s, Vec3 &pos, const Vec2 &size, const Vec4 &color, f32 rotation)
{
    // Bind font shader
    s_Data->m_ShaderLibrary.Get("Font")->Bind();

    // render
    s_Data->m_ShaderLibrary.Get("Font")->SetUniform("u_TextColor", color);

    s_Data->m_fVAO->Bind();

    for (auto c : s)
    {
        auto ch{s_Data->m_Font->GetCharacter(c)};
        float xpos = pos.x + ch.GetBearing().x * size.x;
        float ypos = pos.y - (ch.GetSize().y - ch.GetBearing().y) * size.y;

        float w = ch.GetSize().x * size.x;
        float h = ch.GetSize().y * size.y;

        std::array<f32, 6 * 4> vertices = {
            xpos, ypos + h, 0.0f, 0.0f, xpos,     ypos, 0.0f, 1.0f, xpos + w, ypos,     1.0f, 1.0f,

            xpos, ypos + h, 0.0f, 0.0f, xpos + w, ypos, 1.0f, 1.0f, xpos + w, ypos + h, 1.0f, 0.0f};

        // render glyph texture over quad
        ch.GetTexture()->Bind();
        // update content of VBO memory
        s_Data->m_fVBO->SetSubData(vertices.data(), sizeof(vertices));
        s_Data->m_fVBO->Unbind();

        // render quad
        s_Data->m_fVAO->Bind();
        RenderCommand::DrawArrays(6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        pos.x += (ch.GetAdvance() >> 6) * size.x;
    }
    s_Data->m_fVAO->Unbind();
}

void Renderer2D::SetRectVertexBufferData(const Mat4 &transform, const Vec4 &color, std::array<Vec2, 4> texCoords,
                                         f32 texIndex, f32 tilingFactor, u32 rectVertexCount)
{
    for (u32 i{0}; i < rectVertexCount; i++)
    {
        s_Data->m_RectVertexBufferPtr->m_Position = transform * s_Data->m_RectVertexPositions[i];
        s_Data->m_RectVertexBufferPtr->m_Color = color;
        s_Data->m_RectVertexBufferPtr->m_TexCoord = texCoords[i];
        s_Data->m_RectVertexBufferPtr->m_TexIndex = texIndex;
        s_Data->m_RectVertexBufferPtr->m_TilingFactor = tilingFactor;
        s_Data->m_RectVertexBufferPtr++;
    }
}

void Renderer2D::ResetStats()
{
    memset(&s_Data->m_Stats, 0, sizeof(Stats));
}

Renderer2D::Stats Renderer2D::GetStats()
{
    return s_Data->m_Stats;
}

void Renderer2D::FlushAndReset()
{
    EndScene();

    s_Data->m_RectIndexCount = 0;
    s_Data->m_RectVertexBufferPtr = s_Data->m_RectVertexBufferBase.get();

    s_Data->m_TextureSlotIndex = 1;
}

void Renderer2D::EndScene()
{
    s_Data->m_RECT_VAO->Bind();
    auto dataSize{(u8 *)s_Data->m_RectVertexBufferPtr - (u8 *)s_Data->m_RectVertexBufferBase.get()};
    s_Data->m_RECT_VBO->SetSubData(s_Data->m_RectVertexBufferBase.get(), static_cast<u32>(dataSize));
    Flush();
}

void Renderer2D::Flush()
{
    // Bind all textures in textureslots
    for (u32 i = 0; i < s_Data->m_TextureSlotIndex; i++)
        s_Data->m_TextureSlots[i]->Bind(i);

    RenderCommand::DrawIndexed(s_Data->m_RECT_VAO, s_Data->m_RectIndexCount);

    s_Data->m_Stats.m_DrawCalls++;
}

void Renderer2D::Shutdown()
{
    TERR_PROFILE_FREE_SMART(s_Data);
    s_Data.reset();
}

Renderer2D::~Renderer2D()
{
    // Profile frees
}

} // namespace Terroir