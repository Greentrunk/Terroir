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

#include "Sandbox2D.h"
#include <imgui.h>

Sandbox2D::Sandbox2D(const std::string_view &name) : Layer(name), m_CameraController(1280.0f / 720.0f, false)
{
}

void Sandbox2D::OnAttach()
{
    std::array<f32, 3 * 7> vertices{-0.5f, -0.5f, 0.0f, 0.0f, 0.8f, 0.0f, 1.0f, 0.5f, -0.5f, 0.0f, 0.0f,
                                    0.8f,  0.0f,  1.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.8f, 0.0f,  1.0f};
    std::array<u32, 3> indices{0, 1, 2};

    m_VertexArray = VertexArray::Create();
    auto vertexBuffer = VertexBuffer::Create(&vertices[0], sizeof(vertices));

    BufferLayout layout{{"a_Position", ShaderDataType::Vec3}, {"a_Color", ShaderDataType::Vec4}};
    vertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    auto indexBuffer = IndexBuffer::Create(&indices[0], static_cast<u32>(indices.size()));
    m_VertexArray->SetIndexBuffer(indexBuffer);

    vertexBuffer->Unbind();
    m_VertexArray->Unbind();

    m_SquareVertexArray = VertexArray::Create();

    auto shader1{m_ShaderLibrary.Load()};
}
void Sandbox2D::OnDetach()
{
    Layer::OnDetach();
}
void Sandbox2D::OnUpdate(Timestep dt)
{
    // Update
    m_CameraController.OnUpdate(dt);

    RenderCommand::Clear({.1, 1, .6, 1});
    Renderer::BeginScene(m_CameraController.GetCamera());
    auto shader{m_ShaderLibrary.Get("Default")};
    Renderer::Submit(m_VertexArray, shader, Math::Transform::Scale(Mat4{1.0f}, Vec3{1.5f}));

    Renderer::EndScene();
}
void Sandbox2D::OnDearImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::End();
}
void Sandbox2D::OnEvent(Event &e)
{
    m_CameraController.OnEvent(e);
}
