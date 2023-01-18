
//
// Created by cjp on 1/5/23.
//

#ifndef TERROIR_WINDOWEVENT_H
#define TERROIR_WINDOWEVENT_H

#include "Event.h"
#include "Terroir/pch/Tpch.h"

namespace Terroir
{
class WindowResizeEvent : public Event
{
  public:
    WindowResizeEvent(u32 width, u32 height) : m_Width(width), m_Height(height)
    {
    }

    [[nodiscard]] constexpr u32 GetMWidth() const
    {
        return m_Width;
    }

    [[nodiscard]] constexpr u32 GetMHeight() const
    {
        return m_Height;
    }

    EVENT_CLASS_TYPE(WindowResize);

    EVENT_CLASS_CATEGORY(EventCategoryWindow)

    [[nodiscard]] std::string ToString() const override
    {
        std::stringstream ss;
        ss << "WindowResizeEvent"
           << ": " << m_Width << ", " << m_Height;
        return ss.str();
    }

  private:
    u32 m_Width, m_Height;
};

class WindowCloseEvent : public Event
{
  public:
    WindowCloseEvent() = default;

    EVENT_CLASS_TYPE(WindowClose);

    EVENT_CLASS_CATEGORY(EventCategoryWindow)

    [[nodiscard]] std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName();
        return ss.str();
    }
};
} // namespace Terroir
#endif // TERROIR_WINDOWEVENT_H
