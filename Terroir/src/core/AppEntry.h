#ifndef TERROIR_APPENTRY_H
#define TERROIR_APPENTRY_H

#include "Terroir/pch/Tpch.h"
#include "application/Application.h"

int main(int argc, char **argv)
{
    Terroir::Log::Init();

    auto app{Terroir::CreateApplication()};
    app->Run();
    // delete app

    // Cleanup Subsystems
    // Terroir::Log::Exit();
}

#endif // TERROIR_APPENTRY_H
