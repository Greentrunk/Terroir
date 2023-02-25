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

    // Check for OpenGL 4.5 support
#ifdef TERR_ENABLE_ASSERTS
    int versionMajor;
    int versionMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
    glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

    TERR_ENGINE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5),
                       "Terroir requires at least OpenGL version 4.5!");
}
#endif

void OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
}
} // namespace Terroir
