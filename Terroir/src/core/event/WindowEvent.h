//
// Created by cjp on 1/5/23.
//

#ifndef TERROIR_WINDOWEVENT_H
#define TERROIR_WINDOWEVENT_H

#include "Tpch.h"
#include "Event.h"
#include <Terroir/terroir_export.h>

namespace Terroir
{
	class TERROIR_EXPORT WindowResizeEvent : public EventBaseI
	{
	public:
		WindowResizeEvent(u32 width, u32 height) : m_Width(width), m_Height(height),
												   m_WindowEventType(EventType::Window::Resize)
		{
			m_EventTypeCategory = EventType::Category::Window;
		}

		inline EventType::Window GetWindowEventType() const
		{
			return m_WindowEventType;
		}

		u32 GetMWidth() const
		{
			return m_Width;
		}

		u32 GetMHeight() const
		{
			return m_Height;
		}

		EVENT_GET_NAME(EventType::Window::Resize);

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << m_Width << ", " << m_Height;
			return ss.str();
		}

	private:
		u32 m_Width, m_Height;
		EventType::Window m_WindowEventType;

	};

	class TERROIR_EXPORT WindowCloseEvent : public EventBaseI
	{
	public:
		WindowCloseEvent() : m_WindowEventType(EventType::Window::Close)
		{
			m_EventTypeCategory = EventType::Category::Window;
		}

		inline EventType::Window GetWindowEventType() const
		{
			return m_WindowEventType;
		}

		EVENT_GET_NAME(EventType::Window::Close);

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName();
			return ss.str();
		}

	private:
		EventType::Window m_WindowEventType;
	};
}
#endif //TERROIR_WINDOWEVENT_H
