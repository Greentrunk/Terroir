//
// Created by cjp on 1/6/23.
//

#include "Tpch.h"
#include "core/Assert.h"
#include "GLFWWindow.h"

namespace Terroir
{
	static bool s_GLFWInit = false;

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

			s_GLFWInit = true;
		}

		m_Window = glfwCreateWindow(static_cast<i32>(m_GlfwData.m_WindowWidth),
				static_cast<i32>(m_GlfwData.m_WindowHeight),
				m_GlfwData.m_WindowTitle.c_str(),
				nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		glfwSetWindowUserPointer(m_Window, &m_GlfwData);
		SetVSync(true);
	}

	void GLFWWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);

	}
}

