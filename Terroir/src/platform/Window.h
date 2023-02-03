//
// Created by cjp on 1/9/23.
//

#ifndef TERROIR_WINDOW_H
#define TERROIR_WINDOW_H

#include "Terroir/pch/Tpch.h"
#include "Terroir/src/core/event/Event.h"
#include "Terroir/src/renderer/GraphicsContext.h"

namespace Terroir
{

class WindowProperties
{
  public:
    WindowProperties(const std::string_view &windowTitle, u32 width, u32 height)
        : m_Title(std::move(windowTitle)), m_Width(width), m_Height(height)
    {
    }

    std::string m_Title;
    u32 m_Width;
    u32 m_Height;
};

class Window
{
  public:
    using EventCallbackFn = std::function<void(Event &)>;

    Window() = default;

    virtual ~Window() = default;

    virtual void SetVSync(bool) = 0;

    [[nodiscard]] virtual bool IsVSync() const = 0;

    [[nodiscard]] virtual void *GetNativeWindow() const = 0;

    [[nodiscard]] virtual void *GetContext() const = 0;

    virtual void OnUpdate() = 0;

    virtual inline void SetEventCallback(const EventCallbackFn &cb) = 0;

    [[nodiscard]] virtual u32 GetWindowWidth() const = 0;
    [[nodiscard]] virtual u32 GetWindowHeight() const = 0;

    // For other windowing systems
    static std::unique_ptr<Window> Create(const WindowProperties &);
};
} // namespace Terroir

#endif // TERROIR_WINDOW_H
