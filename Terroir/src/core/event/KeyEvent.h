//
// Created by cjp on 1/5/23.
//

#ifndef TERROIR_KEYEVENT_H
#define TERROIR_KEYEVENT_H

#include <Terroir/terroir_export.h>
#include "Terroir/src/core/Types.h"
#include "Event.h"

namespace Terroir
{
	class TERROIR_EXPORT KeyEventBase : public EventBaseI
	{
	public:
		inline i32 GetKeyCode() const
		{
			return m_KeyCode;
		}


	protected:
		KeyEventBase(i32 keyCode, EventType::Keyboard keyBoardEventType) : m_KeyCode(keyCode),
																		   m_KeyBoardEventType(keyBoardEventType)
		{
			m_EventTypeCategory = EventType::Category::Keyboard;
		}

		inline EventType::Keyboard GetKeyBoardEventType() const
		{
			return m_KeyBoardEventType;
		}


		i32 m_KeyCode;
		EventType::Keyboard m_KeyBoardEventType;
	};

	class TERROIR_EXPORT KeyPressedEvent : public KeyEventBase
	{
	public:
		KeyPressedEvent(i32 keyCode, i32 repeatCount) : KeyEventBase(keyCode, EventType::Keyboard::Pressed),
														m_RepeatCount(repeatCount)
		{
		}

		inline i32 GetRepeatCount() const
		{
			return m_RepeatCount;
		}

		EVENT_GET_NAME(EventType::Keyboard::Pressed);

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << " " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

	private:
		i32 m_RepeatCount;
	};

	class TERROIR_EXPORT KeyReleasedEvent : public KeyEventBase
	{
	public:
		KeyReleasedEvent(i32 keyCode) : KeyEventBase(keyCode, EventType::Keyboard::Released)
		{
		}

		EVENT_GET_NAME(EventType::Keyboard::Released);

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << " " << m_KeyCode;
			return ss.str();
		}
	};
}
#endif //TERROIR_KEYEVENT_H
