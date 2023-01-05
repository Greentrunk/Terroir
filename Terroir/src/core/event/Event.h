//
// Created by cjp on 1/5/23.
//

#ifndef TERROIR_EVENT_H
#define TERROIR_EVENT_H

#include <string>
#include <type_traits>
#include <Terroir/terroir_export.h>
#include "EventType.h"
#include "Terroir/src/log/Log.h"
#include "Terroir/src/core/Types.h"

namespace Terroir
{
	// Base interface class for all events
	class TERROIR_EXPORT EventBaseI
	{
		friend class EventDispatch;

	public:
		~EventBaseI() = default;

		inline EventType::Category GetEventTypeCategory() const
		{
			return m_EventTypeCategory;
		}

		virtual const char* GetName() const = 0;

		virtual std::string ToString() const
		{
			return GetName();
		}


	protected:
		bool m_handled = false;
		EventType::Category m_EventTypeCategory;

	};

	class EventDispatch
	{

	public:
		EventDispatch(EventBaseI& event) : m_Event(event)
		{
		}

		template<typename T, typename F>
		bool Dispatch(const F& f)
		{
			if (m_Event.GetEventTypeCategory() == T::GetEventTypeCategory())
			{
				m_Event.m_handled |= f(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	private:
		EventBaseI& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const EventBaseI& e)
	{
		return os << e.ToString();
	}

	// Macros for inherited events
#define EVENT_GET_NAME(type) const char* GetName() const override {return #type;}


}
#endif //TERROIR_EVENT_H
