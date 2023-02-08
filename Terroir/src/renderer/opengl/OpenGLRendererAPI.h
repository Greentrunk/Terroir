#ifndef TERROIR_OPENGLRENDERERAPI_H
#define TERROIR_OPENGLRENDERERAPI_H

#include "Terroir/src/renderer/RendererAPI.h"
#

namespace Terroir
{

class OpenGLRendererAPI : public RendererAPI
{
  public:
    ~OpenGLRendererAPI() override = default;

    // OpenGL default setups
    void Init() override;

    // Clear screen
    void Clear() override;
    void Clear(const Vec4 &) override;

    void DrawIndexed(const std::shared_ptr<VertexArray> &) override;
};

} // namespace Terroir

#endif // !TERROIR_OPENGLRENDERERAPI_H
