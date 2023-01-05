//
// Created by cjp on 1/5/23.
//

#ifndef TERROIR_APPLICATIONEVENT_H
#define TERROIR_APPLICATIONEVENT_H

#include <Terroir/terroir_export.h>
#include "Event.h"

namespace Terroir
{
	class TERROIR_EXPORT ApplicationEventBase : public EventBaseI
	{
	public:
		ApplicationEventBase(EventType::Application applicationEventType) : m_ApplicationEventType(applicationEventType)
		{
			m_EventTypeCategory = EventType::Category::Application;
		}

		inline EventType::Application GetApplicationEventType() const
		{
			return m_ApplicationEventType;
		}


		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName();
			return ss.str();
		}

	protected:
		EventType::Application m_ApplicationEventType;
	};

	class TERROIR_EXPORT ApplicationTickEvent : public ApplicationEventBase
	{
	public:
		ApplicationTickEvent() : ApplicationEventBase(EventType::Application::Tick)
		{
		}

		EVENT_GET_NAME(EventType::Application::Tick);
	};

	class TERROIR_EXPORT ApplicationUpdateEvent : public ApplicationEventBase
	{
	public:
		ApplicationUpdateEvent() : ApplicationEventBase(EventType::Application::Update)
		{
		}

		EVENT_GET_NAME(EventType::Application::Update);
	};

	class TERROIR_EXPORT ApplicationRenderEvent : public ApplicationEventBase
	{
	public:
		ApplicationRenderEvent() : ApplicationEventBase(EventType::Application::Render)
		{
		}

		EVENT_GET_NAME(EventType::Application::Render);
	};

}
#endif //TERROIR_APPLICATIONEVENT_H
