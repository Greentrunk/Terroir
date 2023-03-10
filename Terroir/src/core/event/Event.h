//
// Created by cjp on 1/5/23.
//

#ifndef TERROIR_EVENT_H
#define TERROIR_EVENT_H

#include <Terroir/pch/Tpch.h>
#include <Terroir/src/core/Types.h>

namespace Terroir
{
#define BIT(x) (1 << x)
enum class EventType
{
    None = 0,
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMoved,
    AppTick,
    AppUpdate,
    AppRender,
    KeyPressed,
    KeyReleased,
    KeyTyped,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled
};

enum EventCategory
{
    None = 0,
    EventCategoryWindow = BIT(0),
    EventCategoryApplication = BIT(1),
    EventCategoryInput = BIT(2),
    EventCategoryKeyboard = BIT(3),
    EventCategoryMouse = BIT(4),
    EventCategoryMouseButton = BIT(5)
};

// Base interface class for all events
class Event
{
    friend class EventDispatch;

  public:
    virtual ~Event() = default;

    bool m_Handled = false;

    [[nodiscard]] virtual const char *GetName() const = 0;

    [[nodiscard]] virtual EventType GetEventType() const = 0;

    [[nodiscard]] virtual i32 GetCategoryFlags() const = 0;

    [[nodiscard]] virtual std::string ToString() const
    {
        return GetName();
    }

    bool IsInCategory(EventCategory category)
    {
        return GetCategoryFlags() & category;
    }
};

class EventDispatch
{
  public:
    explicit EventDispatch(Event &event) : m_Event(event)
    {
    }

    template <typename T, typename F> bool Dispatch(const F &f)
    {
        if (m_Event.GetEventType() == T::GetStaticType())
        {
            m_Event.m_Handled |= f(static_cast<T &>(m_Event));
            return true;
        }
        return false;
    }

  private:
    Event &m_Event;
};

inline std::ostream &operator<<(std::ostream &os, const Event &e)
{
    return os << e.ToString();
}
} // namespace Terroir

// Macros for inherited events
#define EVENT_CLASS_TYPE(type)                                                                                         \
    static EventType GetStaticType()                                                                                   \
    {                                                                                                                  \
        return EventType::type;                                                                                        \
    }                                                                                                                  \
    virtual EventType GetEventType() const override                                                                    \
    {                                                                                                                  \
        return GetStaticType();                                                                                        \
    }                                                                                                                  \
    virtual const char *GetName() const override                                                                       \
    {                                                                                                                  \
        return #type;                                                                                                  \
    }

#define EVENT_CLASS_CATEGORY(category)                                                                                 \
    virtual i32 GetCategoryFlags() const override                                                                      \
    {                                                                                                                  \
        return category;                                                                                               \
    }

#define SET_EVENT_CB_LAMBDA(x) SetEventCallback([this](auto &&PH1) { x(std::forward<decltype(PH1)>(PH1)); })

#define TERR_BIND_EVENT_LAMBDA(fn)                                                                                     \
    [this](auto &&...args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#endif
