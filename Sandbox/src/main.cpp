//
// Created by cjp on 1/3/23.
//

#include <Terroir.h>
#include <imgui.h>
#include <memory>

class TestLayer : public Terroir::Layer
{
  public:
    explicit TestLayer(const std::string &name) : Layer(name)
    {
    }

    ~TestLayer() override
    {
        TERR_APP_DEBUG("DELETING LAYER");
    }

    void OnUpdate() override
    {
        //		TERR_APP_TRACE("{}::Update", m_DebugName);
        if (Terroir::Input::IsKeyPressed(TERR_KEY_TAB))
        {
            TERR_APP_DEBUG("Tab");
        }
    }

    void OnEvent(Terroir::Event &event) override
    {
        TERR_APP_TRACE(event.ToString());
    }

    void OnDearImGuiRender() override
    {
        ImGui::Begin("test");
        ImGui::Text("Hello, Terroir!");
        ImGui::End();
    }
};

class SandboxGame : public Terroir::Application
{
  public:
    SandboxGame()
    {
        PushLayer(std::make_unique<TestLayer>("TEST"));
    }
};

std::unique_ptr<Terroir::Application> Terroir::CreateApplication()
{
    TERR_APP_INFO("Game Initialized!");
    return std::make_unique<SandboxGame>();
}
