//
// Created by cjp on 1/3/23.
//


#include <Terroir.h>
#include <memory>

class TestLayer : public Terroir::Layer
{
public:
	TestLayer(const std::string& name) : Layer(name)
	{
	}

	~TestLayer() override
	{
		TERR_APP_INFO("DELETING LAYER");
	}

	void OnUpdate() override
	{
		TERR_APP_INFO("{}::Update", m_DebugName);
	}

	void OnEvent(Terroir::EventBaseI& event) override
	{
		TERR_APP_INFO(event.ToString());
	}
};

class SandboxGame : public Terroir::Application
{
public:
	SandboxGame()
	{
		PushLayer(std::make_unique<Terroir::Layer*>(new TestLayer("1")));
		PushLayer(std::make_unique<Terroir::Layer*>(new TestLayer("2")));
		PushLayer(std::make_unique<Terroir::Layer*>(new TestLayer("3")));
	}
};

Terroir::Application* Terroir::CreateApplication()
{
	TERR_APP_INFO("Game Initialized!");
	return new SandboxGame();
}