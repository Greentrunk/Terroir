//
// Created by cjp on 1/4/23.
//

#ifndef TERROIR_APPLICATION_H
#define TERROIR_APPLICATION_H

#include "../../dear-imgui/DearImGuiLayer.h"
#include "../../platform/glfw/GLFWWindow.h"
#include "../../renderer/VertexArray.h"
#include "../../renderer/buffer/IndexBuffer.h"
#include "../../renderer/buffer/VertexBuffer.h"
#include "../../renderer/camera/OrthographicCamera.h"
#include "../../renderer/shader/Shader.h"
#include "../Timestep.h"
#include "../event/Event.h"
#include "../event/WindowEvent.h"
#include "../layer/LayerStack.h"

namespace Terroir
{
class Application
{
  public:
    Application(const std::string_view &name = "Terroir App", u32 width = 1280, u32 height = 720);

    static Application &Get()
    {
        return *s_Instance;
    }

    virtual ~Application();

    void Run();

    void OnEvent(Event &);

    void PushLayer(LayerStack::LayerPtr);

    void PushOverlay(LayerStack::LayerPtr);

    Window &GetWindow()
    {
        return *m_Window;
    }

    enum class WindowBackendType
    {
        GLFW
    };

  private:
    bool OnWindowClose(WindowCloseEvent &);
    bool OnWindowResize(WindowResizeEvent &);

    static Application *s_Instance;
    std::unique_ptr<Window> m_Window;

    DearImGuiLayer *m_DearImGuiLayer;
    bool m_Running{true}, m_Minimized{false};
    LayerStack m_LayerStack;
    f32 m_LastFrameTime = 0.0f;
};

// Client defined
std::unique_ptr<Application> CreateApplication();
} // namespace Terroir

#endif // TERROIR_APPLICATION_H
