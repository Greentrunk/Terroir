//
// Created by cjp on 1/4/23.
//

#include "Application.h"
#include "log/Log.h"
#include "core/event/AllEvents.h"

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

		while (true);
	}

	Application::Application()
	{

	}

	Application::~Application()
	{

	}
}