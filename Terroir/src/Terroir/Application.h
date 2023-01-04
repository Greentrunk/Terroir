//
// Created by cjp on 1/4/23.
//

#ifndef TERROIR_APPLICATION_H
#define TERROIR_APPLICATION_H

#include <Terroir/terroir_export.h>

namespace Terroir
{
	class TERROIR_EXPORT Application
	{


	public:
		Application();

		virtual ~Application();

		void Init();
	};

	// Client defined
	Application* CreateApplication();
}


#endif //TERROIR_APPLICATION_H
