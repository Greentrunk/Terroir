//
// Created by cjp on 1/5/23.
//

#ifndef TERROIR_APPLICATIONEVENT_H
#define TERROIR_APPLICATIONEVENT_H

#include "Event.h"

namespace Terroir
{
	class  ApplicationEventBase : public Event
	{
	public:
		ApplicationEventBase() = default;
	};

	class  ApplicationTickEvent : public ApplicationEventBase
	{
	public:
		ApplicationTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick);

		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	};

	class  ApplicationUpdateEvent : public ApplicationEventBase
	{
	public:
		ApplicationUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate);

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class  ApplicationRenderEvent : public ApplicationEventBase
	{
	public:
		ApplicationRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender);

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

}
#endif //TERROIR_APPLICATIONEVENT_H
