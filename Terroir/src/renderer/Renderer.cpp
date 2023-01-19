#include "Renderer.h"
#include "RenderCommand.h"
#include "Tpch.h"
#include "math/Math.h"
#include "renderer/OrthographicCamera.h"

namespace Terroir
{
Renderer::SceneData *Renderer::m_SceneData = new Renderer::SceneData; // NOLINT

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
    shader->UploadUniformMat4("u_ViewProjection", m_SceneData->m_ViewProjectionMatrix);
    shader->UploadUniformMat4("u_Transform", transform);

    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}
} // namespace Terroir
