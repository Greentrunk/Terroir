#ifndef TERROIR_APPENTRY_H
#define TERROIR_APPENTRY_H

#include "Terroir/pch/Tpch.h"
#include "application/Application.h"

int main()
{
    Terroir::Log::Init();

    auto app{Terroir::CreateApplication()};
    //    TERR_PROFILE_ALLOC(app.get(), sizeof(std::unique_ptr<Application>));
    TERR_PROFILE_ALLOC_SMART(app);
    TERR_PROFILE_SCOPE("Terroir Application Run");
    app->Run();
    // delete app

    // Cleanup Subsystems
    // Terroir::Log::Exit();
}

#endif // TERROIR_APPENTRY_H
