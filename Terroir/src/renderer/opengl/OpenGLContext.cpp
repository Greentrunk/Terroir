#include "renderer/opengl/OpenGLContext.h"
#include "Tpch.h"
#include "core/Assert.h"
#include "log/Log.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Terroir
{
OpenGLContext::OpenGLContext(GLFWwindow *windowHandle) : m_WindowHandle(windowHandle)
{
    TERR_ENGINE_ASSERT(m_WindowHandle, "Handle is pointing to nullptr!");
}

OpenGLContext::~OpenGLContext()
{
    TERR_ENGINE_DEBUG("OpenGLContext deleted");
}

void OpenGLContext::Init()
{
    glfwMakeContextCurrent(m_WindowHandle);
    auto status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    TERR_ENGINE_ASSERT(status, "Failed to init Glad!");
}

void OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
}
} // namespace Terroir
