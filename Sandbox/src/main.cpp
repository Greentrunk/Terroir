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
		TERR_APP_DEBUG("DELETING LAYER");
	}

	void OnUpdate() override
	{
		TERR_APP_TRACE("{}::Update", m_DebugName);
	}

	void OnEvent(Terroir::Event& event) override
	{
		TERR_APP_TRACE(event.ToString());
	}
};

class SandboxGame : public Terroir::Application
{
public:
	SandboxGame()
	{
		PushLayer(std::make_unique<Terroir::DearImGuiLayer>());
	}
};

std::unique_ptr<Terroir::Application> Terroir::CreateApplication()
{
	TERR_APP_INFO("Game Initialized!");
	return std::make_unique<SandboxGame>();
}