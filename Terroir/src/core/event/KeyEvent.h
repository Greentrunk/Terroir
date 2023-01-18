//
// Created by cjp on 1/5/23.
//

#ifndef TERROIR_KEYEVENT_H
#define TERROIR_KEYEVENT_H

#include "Event.h"
#include "Terroir/pch/Tpch.h"

namespace Terroir
{
class KeyEventBase : public Event
{
  public:
    [[nodiscard]] constexpr i32 GetKeyCode() const
    {
        return m_KeyCode;
    }

  protected:
    KeyEventBase(i32 keyCode) : m_KeyCode(keyCode)
    {
    }

    i32 m_KeyCode;
};

class KeyPressedEvent : public KeyEventBase
{
  public:
    KeyPressedEvent(i32 keyCode, i32 repeatCount) : KeyEventBase(keyCode), m_RepeatCount(repeatCount)
    {
    }

    [[nodiscard]] constexpr i32 GetRepeatCount() const
    {
        return m_RepeatCount;
    }

    EVENT_CLASS_TYPE(KeyPressed);

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard)

    [[nodiscard]] std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << " " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
        return ss.str();
    }

  private:
    i32 m_RepeatCount;
};

class KeyReleasedEvent : public KeyEventBase
{
  public:
    KeyReleasedEvent(i32 keyCode) : KeyEventBase(keyCode)
    {
    }

    EVENT_CLASS_TYPE(KeyReleased);

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard)

    [[nodiscard]] std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << " " << m_KeyCode;
        return ss.str();
    }
};
} // namespace Terroir
#endif // TERROIR_KEYEVENT_H
