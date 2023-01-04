//
// Created by cjp on 1/4/23.
//

#ifndef TERROIR_APPENTRY_H
#define TERROIR_APPENTRY_H

#include "log/Log.h"

int main(int argc, char** argv)
{
	Terroir::Log::Init();
	TERR_ENGINE_INFO("Test Info");
	TERR_ENGINE_WARN("Test Warn");
	TERR_ENGINE_ERROR("Test Error");
	TERR_ENGINE_CRIT("Test Crit");

	auto app = Terroir::CreateApplication();
	app->Init();
	delete app;
}

#endif //TERROIR_APPENTRY_H
