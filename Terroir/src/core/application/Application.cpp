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
    TERR_PROFILE_SCOPE("Terroir Application Startup");

    // Can't have more than one instance
    TERR_ENGINE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    TERR_ENGINE_INFO("Initializing Terroir Subsystems...");

    // Cross platform window subsystem init
    m_Window = Window::Create({name, width, height});
    TERR_PROFILE_ALLOC_SMART(m_Window);
    m_Window->SET_EVENT_CB_LAMBDA(OnEvent);
    m_Window->SetVSync(false);

    // // Cross platform audio subsystem init
    m_AudioManager = AudioManager::Create({});
    TERR_PROFILE_ALLOC_SMART(m_AudioManager);

    // Cross platform renderer sybsystem init
    Renderer::Init();

    // Layers
    auto dearImGuiLayer = std::make_unique<DearImGuiLayer>();
    m_DearImGuiLayer = dearImGuiLayer.get();
    TERR_PROFILE_ALLOC_SMART(dearImGuiLayer);
    PushOverlay(std::move(dearImGuiLayer));
}

Application::~Application()
{
    TERR_ENGINE_INFO("Exiting Application");
    Renderer::Shutdown();
}

void Application::Run()
{

    TERR_ENGINE_INFO("Terroir Application Initialized");

    while (m_Running)
    {
        TERR_PROFILE_SCOPE("Terroir Application Run Loop");
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

        // Cleanup sounds
        m_AudioManager->Cleanup();
    }
    //    FrameMark;
}

void Application::OnEvent(Event &e)
{
    EventDispatch dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(TERR_BIND_EVENT_LAMBDA(Application::OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(TERR_BIND_EVENT_LAMBDA(Application::OnWindowResize));

    // Iterate through layerstack
    for (auto &layer : std::ranges::reverse_view(m_LayerStack))
    {
        layer->OnEvent(e);
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
