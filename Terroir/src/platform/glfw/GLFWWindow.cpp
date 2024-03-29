//
// Created by cjp on 1/6/23.
//

#include "GLFWWindow.h"
#include "Tpch.h"
#include "core/Assert.h"
#include "core/event/KeyEvent.h"
#include "core/event/MouseEvent.h"
#include "core/event/WindowEvent.h"
#include "renderer/GraphicsContext.h"
#include "renderer/opengl/OpenGLContext.h"
#include <glad/glad.h>
#include <memory>

namespace Terroir
{
static auto s_GLFWInit{false};

static const auto GLFWErrorCallback{
    [](i32 err, const char *desc) { TERR_ENGINE_ERROR("[glfw Error]: ({}): {}", err, desc); }};

GLFWWindow::GLFWWindow(const WindowProperties &props) : m_GlfwData({props.m_Title, props.m_Width, props.m_Height})
{
    GLFWWindow::Init();
}

GLFWWindow::~GLFWWindow()
{
    GLFWWindow::Shutdown();
}

void GLFWWindow::OnUpdate()
{
    TERR_PROFILE_FUNC;
    glfwPollEvents();
    m_Context->SwapBuffers();
}

void GLFWWindow::SetVSync(bool enabled)
{
    TERR_PROFILE_FUNC;
    if (enabled)
    {
        glfwSwapInterval(1);
    }
    else
    {
        glfwSwapInterval(0);
    }
    m_GlfwData.m_WindowVSync = enabled;
}

bool GLFWWindow::IsVSync() const
{
    return m_GlfwData.m_WindowVSync;
}

void GLFWWindow::Init()
{
    TERR_PROFILE_FUNC;
    TERR_ENGINE_INFO("Initializing glfw Window {} of size: ({}, {})", m_GlfwData.m_WindowTitle,
                     m_GlfwData.m_WindowWidth, m_GlfwData.m_WindowHeight);

    if (!s_GLFWInit)
    {
        [[maybe_unused]] auto success{glfwInit()};
        TERR_ENGINE_ASSERT(success, "glfw couldn't be initialized");
        glfwSetErrorCallback(GLFWErrorCallback);
        s_GLFWInit = true;
    }

#ifdef TILING_WM
    // If use with Tiling window manager, set resizeable to FALSE!
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
#else // TILING_WM
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
#endif
    m_Window = glfwCreateWindow(static_cast<i32>(m_GlfwData.m_WindowWidth), static_cast<i32>(m_GlfwData.m_WindowHeight),
                                m_GlfwData.m_WindowTitle.c_str(), nullptr, nullptr);

    m_Context = std::unique_ptr<GraphicsContext>(new OpenGLContext(m_Window));
    TERR_PROFILE_ALLOC_SMART(m_Context);
    m_Context->Init();

    glfwSetWindowUserPointer(m_Window, &m_GlfwData);
    SetVSync(true);

    // glfw Cbs and lambdas
#define GET_WINDOW_USER_POINTER() auto &data{*static_cast<GlfwData *>(glfwGetWindowUserPointer(window))};

    auto WindowSizeCallback{[](GLFWwindow *window, i32 width, i32 height) {
        GET_WINDOW_USER_POINTER();

        data.m_WindowWidth = width;
        data.m_WindowHeight = height;

        WindowResizeEvent event(width, height);
        data.m_WindowCb(event);
    }};

    auto WindowCloseCallback{[](GLFWwindow *window) {
        GET_WINDOW_USER_POINTER();

        WindowCloseEvent event;
        data.m_WindowCb(event);
    }};

    auto KeyCallback{[](GLFWwindow *window, i32 key, i32 scancode, i32 action, i32 mods) {
        GET_WINDOW_USER_POINTER();

        switch (action)
        {
        case GLFW_PRESS: {
            KeyPressedEvent event(key, 0);
            data.m_WindowCb(event);
            break;
        }
        case GLFW_RELEASE: {
            KeyReleasedEvent event(key);
            data.m_WindowCb(event);
            break;
        }
        case GLFW_REPEAT: {
            KeyPressedEvent event(key, 1);
            data.m_WindowCb(event);
            break;
        }
        default:
            break;
        }
    }};

    auto MouseButtonCallback{[](GLFWwindow *window, i32 button, i32 action, i32 mods) {
        GET_WINDOW_USER_POINTER();

        switch (action)
        {
        case GLFW_PRESS: {
            MouseButtonPressedEvent event(button);
            data.m_WindowCb(event);
            break;
        }
        case GLFW_RELEASE: {
            MouseButtonReleasedEvent event(button);
            data.m_WindowCb(event);
            break;
        }
        default:
            break;
        }
    }};

    auto MouseScrollCallback{[](GLFWwindow *window, f64 xOffset, f64 yOffset) {
        GET_WINDOW_USER_POINTER();

        MouseScrolledEvent event(static_cast<f32>(xOffset), static_cast<f32>(yOffset));
        data.m_WindowCb(event);
    }};

    auto MouseCursorCallback{[](GLFWwindow *window, f64 xPos, f64 yPos) {
        GET_WINDOW_USER_POINTER();

        MouseMovedEvent event(static_cast<f32>(xPos), static_cast<f32>(yPos));
        data.m_WindowCb(event);
    }};

    glfwSetWindowSizeCallback(m_Window, WindowSizeCallback);
    glfwSetWindowCloseCallback(m_Window, WindowCloseCallback);
    glfwSetKeyCallback(m_Window, KeyCallback);
    glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
    glfwSetScrollCallback(m_Window, MouseScrollCallback);
    glfwSetCursorPosCallback(m_Window, MouseCursorCallback);
}

void GLFWWindow::Shutdown()
{
    TERR_PROFILE_FUNC;
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}
} // namespace Terroir
