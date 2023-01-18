#include "OpenGLRendererAPI.h"
#include "Tpch.h"
#include <glad/glad.h>

namespace Terroir
{
void OpenGLRendererAPI::Clear()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::Clear(const glm::vec4 &color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray)
{
    glDrawElements(GL_TRIANGLES, static_cast<i32>(vertexArray->GetIndexBuffer()->GetIndexCount()), GL_UNSIGNED_INT,
                   nullptr);
}

} // namespace Terroir
