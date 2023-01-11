//
// Created by cjp on 1/4/23.
//

#include "Application.h"
#include "Tpch.h"
#include "core/Assert.h"
#include "core/event/ApplicationEvent.h"
#include "core/event/KeyEvent.h"
#include "core/event/MouseEvent.h"
#include "core/event/WindowEvent.h"
#include "dear-imgui/DearImGuiLayer.h"
#include "log/Log.h"
#include "platform/Input.h"
#include <algorithm>
#include <glad/glad.h>
#include <memory>

namespace Terroir
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
#define SET_EVENT_CB_LAMBDA(x) SetEventCallback([this](auto &&PH1) { x(std::forward<decltype(PH1)>(PH1)); })
// #define EVENT_LAMBDA(x) [this](auto && PH1) { x(std::forward<decltype(PH1)>(PH1)); }

Application *Application::s_Instance{nullptr};

void Application::Run()
{

    TERR_ENGINE_INFO("Terroir Application Initialized");

    while (m_Running)
    {
        glClearColor(.2, .5, .4, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto &layer : m_LayerStack)
        {
            layer->OnUpdate();
        }
        m_DearImGuiLayer->Begin();
        for (auto &layer : m_LayerStack)
        {
            layer->OnDearImGuiRender();
        }
        m_DearImGuiLayer->End();

        m_Window->OnUpdate();
    }
}

Application::Application()
{
    TERR_ENGINE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    constexpr u32 defaultWidth{2000}, defaultHeight{2000};
    auto window{Window::Create({"Terroir Engine", defaultWidth, defaultHeight})};
    m_Window = std::unique_ptr<Window>(window);
    m_Window->SET_EVENT_CB_LAMBDA(OnEvent);

    m_DearImGuiLayer = std::make_shared<DearImGuiLayer>();
    PushOverlay(std::move(m_DearImGuiLayer));
}

Application::Application(const std::string &name, u32 width, u32 height)
{
    TERR_ENGINE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    auto window{Window::Create({name, width, height})};
    m_Window = std::unique_ptr<Window>(window);
    m_Window->SET_EVENT_CB_LAMBDA(OnEvent);

    m_DearImGuiLayer = std::make_shared<DearImGuiLayer>();
    PushOverlay(std::move(m_DearImGuiLayer));
}

Application::~Application()
{
    TERR_ENGINE_INFO("Exiting Application");
}

void Application::OnEvent(Event &e)
{
    EventDispatch dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
    TERR_ENGINE_INFO(e.ToString());

    // Iterate through layerstack
    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
    {
        (*--it)->OnUpdate();
        if (e.m_Handled)
            break;
    }
}

bool Application::OnWindowClose(WindowCloseEvent &)
{
    m_Running = false;
    return true;
}

void Application::PushLayer(LayerStack::LayerPtr layer)
{
    layer->OnAttach();
    m_LayerStack.PushLayer(layer);
}

void Application::PushOverlay(LayerStack::LayerPtr overlay)
{
    overlay->OnAttach();
    m_LayerStack.PushOverlay(overlay);
}
} // namespace Terroir
