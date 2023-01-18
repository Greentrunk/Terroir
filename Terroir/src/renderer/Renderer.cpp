#include "Renderer.h"
#include "RenderCommand.h"
#include "Tpch.h"
#include "renderer/OrthographicCamera.h"

namespace Terroir
{
Renderer::SceneData *Renderer::m_SceneData = new Renderer::SceneData;

void Renderer::BeginScene(OrthographicCamera &camera)
{
    m_SceneData->m_ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene()
{
}

void Renderer::Submit(const std::shared_ptr<VertexArray> &vertexArray, const std::shared_ptr<Shader> &shader)
{
    // To be used with multiple threads
    shader->Bind();
    shader->UploadUniformMat4("u_ViewProjection", m_SceneData->m_ViewProjectionMatrix);

    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}
} // namespace Terroir
