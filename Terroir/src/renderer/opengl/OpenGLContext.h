#ifndef TERROIR_OPENGLCONTEXT_H
#define TERROIR_OPENGLCONTEXT_H

#include "../GraphicsContext.h"
#include <GLFW/glfw3.h>

namespace Terroir
{
class OpenGLContext : public GraphicsContext
{
  public:
    OpenGLContext(GLFWwindow *);
    ~OpenGLContext() override;

    void Init() override;
    void SwapBuffers() override;

  private:
    GLFWwindow *m_WindowHandle;
};

} // namespace Terroir
#endif
