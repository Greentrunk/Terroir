#ifndef TERROIR_APPENTRY_H
#define TERROIR_APPENTRY_H

#include "Terroir/pch/Tpch.h"
#include "application/Application.h"

int main(int argc, char **argv)
{
    Terroir::Log::Init();
    TERR_ENGINE_TRACE("Test Trace");
    TERR_ENGINE_DEBUG("Test Debug");
    TERR_ENGINE_INFO("Test Info");
    TERR_ENGINE_WARN("Test Warn");
    TERR_ENGINE_ERROR("Test Error");
    TERR_ENGINE_CRIT("Test Crit");

    auto app{Terroir::CreateApplication()};
    app->Run();
    // delete app

    // Cleanup Subsystems
    // Terroir::Log::Exit();
}

#endif // TERROIR_APPENTRY_H
