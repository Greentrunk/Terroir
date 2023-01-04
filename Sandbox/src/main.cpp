//
// Created by cjp on 1/3/23.
//
#include <Terroir/src/Terroir.h>

class SandboxGame : public Terroir::Application
{


public:
	SandboxGame()
	{
	}
};

Terroir::Application* Terroir::CreateApplication()
{
	return new SandboxGame();
}