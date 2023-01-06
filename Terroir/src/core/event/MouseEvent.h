//
// Created by cjp on 1/5/23.
//

#ifndef TERROIR_MOUSEEVENT_H
#define TERROIR_MOUSEEVENT_H

#include "Tpch.h"
#include <Terroir/terroir_export.h>
#include "Event.h"

namespace Terroir
{
	class TERROIR_EXPORT MouseMovedEvent : public EventBaseI
	{
	public:
		MouseMovedEvent(f32 x, f32 y) : m_MouseX(x), m_MouseY(x), m_MouseEventType(EventType::Mouse::Moved)
		{
			m_EventTypeCategory = EventType::Category::Mouse;
		}

		inline EventType::Mouse GetMouseEventType() const
		{
			return m_MouseEventType;
		}

		inline f32 GetMouseY() const
		{
			return m_MouseY;
		}

		inline f32 GetMouseX() const
		{
			return m_MouseX;
		}

		EVENT_GET_NAME(EventType::Mouse::Moved);

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

	private:
		f32 m_MouseX, m_MouseY;
		EventType::Mouse m_MouseEventType;

	};

	class TERROIR_EXPORT MouseScrolledEvent : public EventBaseI
	{
	public:
		MouseScrolledEvent(f32 x, f32 y) : m_XOffset(x), m_YOffset(x), m_MouseEventType(EventType::Mouse::Scrolled)
		{
			m_EventTypeCategory = EventType::Category::Mouse;
		}

		inline EventType::Mouse GetMouseEventType() const
		{
			return m_MouseEventType;
		}

		inline f32 GetXOffset() const
		{
			return m_YOffset;
		}

		inline f32 GetYOffset() const
		{
			return m_XOffset;
		}

		EVENT_GET_NAME(EventType::Mouse::Scrolled);

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

	private:
		f32 m_XOffset, m_YOffset;
		EventType::Mouse m_MouseEventType;

	};

	class TERROIR_EXPORT MouseButtonEvent : public EventBaseI
	{
	public:
		inline i32 GetMouseButton() const
		{
			return m_Button;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << m_Button;
			return ss.str();
		}

		inline EventType::Mouse GetMouseEventType() const
		{
			return m_MouseEventType;
		}

	protected:
		MouseButtonEvent(i32 button, EventType::Mouse mouseEventType) : m_Button(button),
																		m_MouseEventType(mouseEventType)
		{
			m_EventTypeCategory = EventType::Category::Mouse;
		}

		i32 m_Button;
		EventType::Mouse m_MouseEventType;
	};

	class TERROIR_EXPORT MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(i32 button) : MouseButtonEvent(button, EventType::Mouse::Pressed)
		{
		}

		EVENT_GET_NAME(EventType::Mouse::Pressed);
	};

	class TERROIR_EXPORT MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(i32 button) : MouseButtonEvent(button, EventType::Mouse::Released)
		{
		}

		EVENT_GET_NAME(EventType::Mouse::Released);
	};
}

#endif //TERROIR_MOUSEEVENT_H
