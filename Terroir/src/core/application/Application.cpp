//
// Created by cjp on 1/4/23.
//

#include "Tpch.h"
#include "Application.h"
#include "core/event/AllEvents.h"
#include <GLFW/glfw3.h>

namespace Terroir
{
	void Application::Init()
	{

		TERR_ENGINE_INFO("Terroir Application Initialized");

		// TESTS
		KeyPressedEvent e(42, 4);
		WindowCloseEvent w;
		ApplicationRenderEvent ru;
		MouseButtonPressedEvent mbp(4);
		MouseScrolledEvent ms(2.0f, 3.0f);

		TERR_ENGINE_INFO(e.ToString());
		TERR_ENGINE_INFO(w.ToString());
		TERR_ENGINE_INFO(mbp.ToString());
		TERR_ENGINE_INFO(ru.ToString());
		TERR_ENGINE_INFO(w.ToString());
		TERR_ENGINE_INFO(ms.ToString());

		while (m_Running)
		{
			glClearColor(0, 2, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	Application::Application()
	{
		m_Window = WindowBaseI::Create({ "Terroir Engine", 100, 100 });
	}

	Application::Application(const std::string& name, u32 width, u32 height)
	{
		m_Window = WindowBaseI::Create({ name, width, height });

	}

	Application::~Application()
	{

	}
}