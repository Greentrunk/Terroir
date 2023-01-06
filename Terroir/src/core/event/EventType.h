//
// Created by cjp on 1/5/23.
//

#ifndef TERROIR_EVENTTYPE_H
#define TERROIR_EVENTTYPE_H

#include <Terroir/terroir_export.h>

// Enums representing different events that can fire during a Terroir application

namespace Terroir
{
	class TERROIR_EXPORT EventType
	{
	public:
		enum class TERROIR_EXPORT Category
		{
			None = 0,
			Window,
			Application,
			Keyboard,
			Mouse
		};
		enum class TERROIR_EXPORT Window
		{
			None = 0,
			Close,
			Resize,
			Focus,
			LostFocus,
			Moved
		};

		enum class TERROIR_EXPORT Application
		{
			None = 0,
			Tick,
			Update,
			Render
		};

		enum class TERROIR_EXPORT Keyboard
		{
			None = 0,
			Pressed,
			Released
		};

		enum class TERROIR_EXPORT Mouse
		{
			None = 0,
			Pressed,
			Released,
			Moved,
			Scrolled
		};

	};
}
#endif //TERROIR_EVENTTYPE_H
