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

#include "Renderer.h"
#include "RenderCommand.h"
#include "Tpch.h"
#include "math/Math.h"
#include "renderer/opengl/OpenGLShader.h"

namespace Terroir
{
std::unique_ptr<Renderer::SceneData> Renderer::m_SceneData = std::make_unique<Renderer::SceneData>();

void Renderer::Init()
{
    RenderCommand::Init();
}

void Renderer::BeginScene(OrthographicCamera &camera)
{
    m_SceneData->m_ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene()
{
}

void Renderer::Submit(const std::shared_ptr<VertexArray> &vertexArray, const std::shared_ptr<Shader> &shader,
                      const Mat4 &transform)
{
    // To be used with multiple threads
    shader->Bind();
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniform("u_ViewProjection",
                                                                   m_SceneData->m_ViewProjectionMatrix);
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniform("u_Transform", transform);

    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}
void Renderer::OnWindowResize(u32 width, u32 height)
{
    // Will be reworked depending on frame buffers
    RenderCommand::SetViewport(0, 0, width, height);
}
} // namespace Terroir
