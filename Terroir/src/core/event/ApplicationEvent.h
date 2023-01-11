//
// Created by cjp on 1/5/23.
//

#ifndef TERROIR_APPLICATIONEVENT_H
#define TERROIR_APPLICATIONEVENT_H

#include <Terroir/terroir_export.h>
#include "Event.h"

namespace Terroir
{
	class TERROIR_EXPORT ApplicationEventBase : public Event
	{
	public:
		ApplicationEventBase() = default;
	};

	class TERROIR_EXPORT ApplicationTickEvent : public ApplicationEventBase
	{
	public:
		ApplicationTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick);

		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	};

	class TERROIR_EXPORT ApplicationUpdateEvent : public ApplicationEventBase
	{
	public:
		ApplicationUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate);

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class TERROIR_EXPORT ApplicationRenderEvent : public ApplicationEventBase
	{
	public:
		ApplicationRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender);

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

}
#endif //TERROIR_APPLICATIONEVENT_H