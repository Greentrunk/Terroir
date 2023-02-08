#include "Renderer.h"
#include "RenderCommand.h"
#include "Tpch.h"
#include "math/Math.h"
#include "renderer/OrthographicCamera.h"
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
} // namespace Terroir
