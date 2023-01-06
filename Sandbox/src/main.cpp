//
// Created by cjp on 1/3/23.
//


#include <Terroir.h>

class SandboxGame : public Terroir::Application
{


public:
	SandboxGame()
	{
	}
};

Terroir::Application* Terroir::CreateApplication()
{
	TERR_APP_INFO("Game Initialized!");
	return new SandboxGame();
}