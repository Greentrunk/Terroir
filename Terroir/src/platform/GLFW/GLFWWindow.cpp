//
// Created by cjp on 1/6/23.
//

#include "Tpch.h"
#include "core/Assert.h"
#include "GLFWWindow.h"
#include "core/event/WindowEvent.h"
#include "core/event/KeyEvent.h"
#include "core/event/MouseEvent.h"

namespace Terroir
{
	static bool s_GLFWInit = false;

	static auto GLFWErrorCallback = [](i32 err, const char* desc)
	{
		TERR_ENGINE_ERROR("[GLFW Error]: ({}): {}", err, desc);
	};

	std::unique_ptr<WindowBaseI> WindowBaseI::Create(const WindowProperties& props)
	{
		return std::make_unique<GLFWWindow>(props);
	}


	GLFWWindow::~GLFWWindow()
	{
		Shutdown();
	}

	void GLFWWindow::OnUpdate()
	{

		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void GLFWWindow::SetVSync(bool enabled)
	{
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
		TERR_ENGINE_INFO("Initializing GLFW Window {} of size: ({}, {})", m_GlfwData.m_WindowTitle,
				m_GlfwData.m_WindowWidth,
				m_GlfwData.m_WindowHeight);

		if (!s_GLFWInit)
		{
			[[maybe_unused]] auto success = glfwInit();
			TERR_ENGINE_ASSERT(success, "GLFW couldn't be initialized");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInit = true;
		}

#ifdef TILING_WM
		// If use with Tiling window manager, set resizeable to FALSE!
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
#endif
		m_Window = glfwCreateWindow(static_cast<i32>(m_GlfwData.m_WindowWidth),
				static_cast<i32>(m_GlfwData.m_WindowHeight),
				m_GlfwData.m_WindowTitle.c_str(),
				nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		glfwSetWindowUserPointer(m_Window, &m_GlfwData);
		SetVSync(true);

		// GLFW Cbs and lambdas
#define GET_WINDOW_USER_POINTER() auto& data = *(GlfwData*)glfwGetWindowUserPointer(window);

		auto WindowSizeCallback = [](GLFWwindow* window, i32 width, i32 height)
		{
			GET_WINDOW_USER_POINTER();

			data.m_WindowWidth = width;
			data.m_WindowHeight = height;

			WindowResizeEvent event(width, height);
			data.m_WindowCb(event);
		};

		auto WindowCloseCallback = [](GLFWwindow* window)
		{
			GET_WINDOW_USER_POINTER();

			WindowCloseEvent event;
			data.m_WindowCb(event);
		};

		auto KeyCallback = [](GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods)
		{
			GET_WINDOW_USER_POINTER();

			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.m_WindowCb(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.m_WindowCb(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				data.m_WindowCb(event);
				break;
			}
			}
		};

		auto MouseButtonCallback = [](GLFWwindow* window, i32 button, i32 action, i32 mods)
		{
			GET_WINDOW_USER_POINTER();

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.m_WindowCb(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.m_WindowCb(event);
				break;
			}
			}
		};

		auto MouseScrollCallback = [](GLFWwindow* window, f64 xOffset, f64 yOffset)
		{
			GET_WINDOW_USER_POINTER();

			MouseScrolledEvent event(static_cast<f32>(xOffset), static_cast<f32>(yOffset));
			data.m_WindowCb(event);
		};

		auto MouseCursorCallback = [](GLFWwindow* window, f64 xPos, f64 yPos)
		{
			GET_WINDOW_USER_POINTER();

			MouseMovedEvent event(static_cast<f32>(xPos), static_cast<f32>(yPos));
			data.m_WindowCb(event);
		};

		glfwSetWindowSizeCallback(m_Window, WindowSizeCallback);
		glfwSetWindowCloseCallback(m_Window, WindowCloseCallback);
		glfwSetKeyCallback(m_Window, KeyCallback);
		glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
		glfwSetScrollCallback(m_Window, MouseScrollCallback);
		glfwSetCursorPosCallback(m_Window, MouseCursorCallback);
	}

	void GLFWWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);

	}
}

