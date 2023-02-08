#include "OpenGLRendererAPI.h"
#include "Terroir/src/math/Math.h"
#include "Tpch.h"
#include <glad/glad.h>

namespace Terroir
{
void OpenGLRendererAPI::Init()
{
    // Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLRendererAPI::Clear()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::Clear(const Vec4 &color)
{
    glClearColor(color.r, color.g, color.b, color.a); // NOLINT
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray)
{
    glDrawElements(GL_TRIANGLES, static_cast<i32>(vertexArray->GetIndexBuffer()->GetIndexCount()), GL_UNSIGNED_INT,
                   nullptr);
}

} // namespace Terroir
