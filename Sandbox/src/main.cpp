//
// Created by cjp on 1/3/23.
//

#include <Terroir/Terroir.h>

class SandboxGame : public Terroir::Application
{


public:
	SandboxGame()
	{
	}
};

Terroir::Application* Terroir::CreateApplication()
{
	TERR_APP_INFO("Game Initalized!");
	return new SandboxGame();
}