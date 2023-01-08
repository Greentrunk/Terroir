//
// Created by cjp on 1/4/23.
//

#include "Tpch.h"
#include "Application.h"
#include "core/event/WindowEvent.h"
#include "core/event/ApplicationEvent.h"
#include "core/event/KeyEvent.h"
#include "core/event/MouseEvent.h"
#include <GLFW/glfw3.h>

namespace Terroir
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
#define SET_EVENT_CB_LAMBDA(x) SetEventCallback([this](auto&& PH1) { x(std::forward<decltype(PH1)>(PH1)); })
//#define EVENT_LAMBDA(x) [this](auto && PH1) { x(std::forward<decltype(PH1)>(PH1)); }

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

			for (auto& layer: m_LayerStack)
			{
				(*layer)->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}

	Application::Application()
	{
		m_Window = WindowBaseI::Create({ "Terroir Engine", 1200, 900 });
		m_Window->SET_EVENT_CB_LAMBDA(OnEvent);
	}

	Application::Application(const std::string& name, u32 width, u32 height)
	{
		m_Window = WindowBaseI::Create({ name, width, height });
		m_Window->SET_EVENT_CB_LAMBDA(OnEvent);

	}

	Application::~Application()
	{
		TERR_ENGINE_INFO("Exiting Application");
	}

	void Application::OnEvent(EventBaseI& e)
	{
		EventDispatch dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		TERR_ENGINE_INFO(e.ToString());

		// Iterate through layerstack
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(**--it)->OnUpdate();
			if (e.m_Handled) break;

		}
	}

	bool Application::OnWindowClose(WindowCloseEvent&)
	{
		m_Running = false;
		return true;
	}

	void Application::PushLayer(LayerStack::LayerPtr layer)
	{
		m_LayerStack.PushLayer(std::move(layer));
	}

	void Application::PushOverlay(LayerStack::LayerPtr overlay)
	{
		m_LayerStack.PushOverlay(std::move(overlay));
	}
}