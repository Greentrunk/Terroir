//
// Created by cjp on 1/6/23.
//

#ifndef TERROIR_GLFWWINDOW_H
#define TERROIR_GLFWWINDOW_H

#include "Terroir/pch/Tpch.h"
#include "Terroir/src/core/event/Event.h"
#include "Terroir/src/platform/Window.h"
#include <GLFW/glfw3.h>
#include <Terroir/terroir_export.h>

namespace Terroir
{
class TERROIR_EXPORT GLFWWindow : public Window
{

  public:
    explicit GLFWWindow(const WindowProperties &props) : m_GlfwData({props.m_Title, props.m_Width, props.m_Height})
    {
        GLFWWindow::Init();
    }

    ~GLFWWindow() override;

    void OnUpdate() override;

    inline u32 GetWindowWidth() const override
    {
        return m_GlfwData.m_WindowWidth;
    }

    inline u32 GetWindowHeight() const override
    {
        return m_GlfwData.m_WindowHeight;
    }

    inline void SetEventCallback(const EventCallbackFn &cb) override
    {
        m_GlfwData.m_WindowCb = cb;
    }

    void SetVSync(bool) override;

    bool IsVSync() const override;

    inline void *GetNativeWindow() const override
    {
        return m_Window;
    }

  private:
    void Init();

    void Shutdown();

    GLFWwindow *m_Window = nullptr;

    using GlfwData = struct GlfwData
    {
        std::string m_WindowTitle;
        u32 m_WindowWidth, m_WindowHeight;
        bool m_WindowVSync;
        EventCallbackFn m_WindowCb;
    };

    GlfwData m_GlfwData;
};

} // namespace Terroir

#endif // TERROIR_GLFWWINDOW_H
