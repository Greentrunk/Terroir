#include "renderer/opengl/OpenGLContext.h"
#include "Tpch.h"
#include "core/Assert.h"
#include "log/Log.h"
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

    TERR_ENGINE_INFO("OpenGL Renderer initiated");
    TERR_ENGINE_INFO("OpenGL Info:");
    TERR_ENGINE_INFO("Vendor: {}", reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
    TERR_ENGINE_INFO("Renderer: {}", reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
    TERR_ENGINE_INFO("Version: {}", reinterpret_cast<const char *>(glGetString(GL_VERSION)));
}

void OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
}
} // namespace Terroir
