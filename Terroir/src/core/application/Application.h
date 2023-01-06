//
// Created by cjp on 1/4/23.
//

#ifndef TERROIR_APPLICATION_H
#define TERROIR_APPLICATION_H

#include "Terroir/pch/Tpch.h"
#include <Terroir/terroir_export.h>
#include "Terroir/src/platform/Window.h"

namespace Terroir
{
	class TERROIR_EXPORT Application
	{
	public:
		Application();

		Application(const std::string& name, u32 width, u32 height);

		virtual ~Application();

		void Init();

	private:
		std::unique_ptr<WindowBaseI> m_Window;
		bool m_Running = true;
	};

	// Client defined
	Application* CreateApplication();
}


#endif //TERROIR_APPLICATION_H
