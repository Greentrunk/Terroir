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
#include "renderer/Renderer.h"
#include "renderer/VertexArray.h"
#include "renderer/buffer/BufferLayout.h"
#include "renderer/buffer/IndexBuffer.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Terroir
{

Application *Application::s_Instance{nullptr};

Application::Application(const std::string_view &name, u32 width, u32 height)
{
    // Can't have more than one instance
    TERR_ENGINE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    // Cross platform window subsystem init
    m_Window = Window::Create({name, width, height});
    // m_Window = std::unique_ptr<Window>(window);
    m_Window->SET_EVENT_CB_LAMBDA(OnEvent);
    m_Window->SetVSync(false);

    // Cross platform renderer sybsystem init
    Renderer::Init();

    // Layers
    auto dearImGuiLayer{std::make_unique<DearImGuiLayer>()};
    m_DearImGuiLayer = dearImGuiLayer.get();
    PushOverlay(std::move(dearImGuiLayer));
}

Application::~Application()
{
    TERR_ENGINE_INFO("Exiting Application");
}

void Application::Run()
{
    TERR_ENGINE_INFO("Terroir Application Initialized");

    while (m_Running)
    {
        // temporary
        // Calculate delta-time
        auto time = static_cast<f32>(glfwGetTime());
        Timestep timestep{time - m_LastFrameTime};
        m_LastFrameTime = time;

        // If the window is minimized, don't render anything
        if (!m_Minimized)
        {
            for (auto &layer : m_LayerStack)
            {
                layer->OnUpdate(timestep);
            }
        }

        // Continue to render Dear ImGui
        m_DearImGuiLayer->Begin();
        for (auto &layer : m_LayerStack)
        {
            layer->OnDearImGuiRender();
        }
        m_DearImGuiLayer->End();

        m_Window->OnUpdate();
    }
}

void Application::OnEvent(Event &e)
{
    EventDispatch dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(TERR_BIND_EVENT_LAMBDA(Application::OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(TERR_BIND_EVENT_LAMBDA(Application::OnWindowResize));

    // Iterate through layerstack
    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
    {
        (*--it)->OnEvent(e);
        if (e.m_Handled)
            break;
    }
}

bool Application::OnWindowClose(WindowCloseEvent &)
{
    m_Running = false;
    return true;
}

bool Application::OnWindowResize(WindowResizeEvent &e)
{
    if (e.GetWidth() == 0 || e.GetHeight() == 0)
    {
        m_Minimized = true;
        return false;
    }

    m_Minimized = false;
    Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

    return false;
}

void Application::PushLayer(LayerStack::LayerPtr layer)
{
    layer->OnAttach();
    m_LayerStack.PushLayer(std::move(layer));
}

void Application::PushOverlay(LayerStack::LayerPtr overlay)
{
    overlay->OnAttach();
    m_LayerStack.PushOverlay(std::move(overlay));
}

} // namespace Terroir
