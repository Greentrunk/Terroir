//
// Created by cjp on 1/6/23.
//

#ifndef TERROIR_GLFWWINDOW_H
#define TERROIR_GLFWWINDOW_H

#include "Terroir/pch/Tpch.h"
#include "Terroir/src/core/event/Event.h"
#include "Terroir/src/platform/Window.h"
#include "Terroir/src/renderer/GraphicsContext.h"
#include <GLFW/glfw3.h>

namespace Terroir
{
class GLFWWindow : public Window
{

  public:
    explicit GLFWWindow(const WindowProperties &props);

    ~GLFWWindow() override;

    void OnUpdate() override;

    [[nodiscard]] constexpr u32 GetWindowWidth() const override
    {
        return m_GlfwData.m_WindowWidth;
    }

    [[nodiscard]] constexpr u32 GetWindowHeight() const override
    {
        return m_GlfwData.m_WindowHeight;
    }

    void SetEventCallback(const EventCallbackFn &cb) override
    {
        m_GlfwData.m_WindowCb = cb;
    }

    void SetVSync(bool) override;

    [[nodiscard]] bool IsVSync() const override;

    [[nodiscard]] constexpr void *GetNativeWindow() const override
    {
        return m_Window;
    }

    [[nodiscard]] void *GetContext() const override
    {
        return m_Context.get();
    }

  private:
    void Init();

    void Shutdown();

    GLFWwindow *m_Window = nullptr;
    std::unique_ptr<GraphicsContext> m_Context;

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
