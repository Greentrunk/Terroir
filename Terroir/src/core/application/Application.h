//
// Created by cjp on 1/4/23.
//

#ifndef TERROIR_APPLICATION_H
#define TERROIR_APPLICATION_H

#include "../../dear-imgui/DearImGuiLayer.h"
#include "../../platform/glfw/GLFWWindow.h"
#include "../event/Event.h"
#include "../event/WindowEvent.h"
#include "../layer/LayerStack.h"
#include <Terroir/terroir_export.h>

namespace Terroir
{
class TERROIR_EXPORT Application
{
  public:
    Application();

    Application(const std::string &name, u32 width, u32 height);

    inline static Application &Get()
    {
        return *s_Instance;
    }

    virtual ~Application();

    void Run();

    void OnEvent(Event &);

    void PushLayer(LayerStack::LayerPtr);

    void PushOverlay(LayerStack::LayerPtr);

    inline Window &GetWindow()
    {
        return *m_Window;
    }

    enum class WindowBackendType
    {
        GLFW
    };

  private:
    bool OnWindowClose(WindowCloseEvent &);

    static Application *s_Instance;
    std::unique_ptr<Window> m_Window;
    std::shared_ptr<DearImGuiLayer> m_DearImGuiLayer;
    bool m_Running{true};
    LayerStack m_LayerStack;
};

// Client defined
std::unique_ptr<Application> CreateApplication();
} // namespace Terroir

#endif // TERROIR_APPLICATION_H
