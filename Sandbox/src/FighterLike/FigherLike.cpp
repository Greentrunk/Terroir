#include "FighterLike.h"
#include <imgui.h>

FighterLike::FighterLike(const std::string_view &name) : Layer(name)
{
    CreateCamera(Application::Get().GetWindowWidth(), Application::Get().GetWindowHeight());
}

void FighterLike::OnAttach()
{
    m_SpriteSheet = Texture2D::Create("Sandbox/assets/textures/colored-transparent_packed.png");
}

void FighterLike::OnDetach()
{
}

void FighterLike::OnUpdate(Timestep dt)
{
    TERR_PROFILE_FUNC;

    // Reset Renderer statistics
    Renderer2D::ResetStats();

    // Clear Screen to color of choice
    RenderCommand::Clear(Color::BLACK);

    // Start draw calls
    Renderer2D::BeginScene(*m_Camera);

    Sprite allSprites(m_SpriteSheet, {0.0f, 0.0f}, {0.0f, 0.0f});
    Sprite sprite(m_SpriteSheet, {0, 20}, {16, 16});
    Renderer2D::DrawSprite(sprite);
    // Renderer2D::DrawSprite(allSprites);

    Renderer2D::EndScene();           // Finish draw calls before this
}
void FighterLike::OnDearImGuiRender() // Optional gui rendering
{
    TERR_PROFILE_FUNC;

    const auto stats{Renderer2D::GetStats()};
    ImGui::Begin("Settings");
    ImGui::Text("Renderer2D Stats:");
    ImGui::Text("Draw Calls: %d", stats.m_DrawCalls);
    ImGui::Text("Rects: %d", stats.m_RectCount);
    ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
    ImGui::End();
}

void FighterLike::OnEvent(Event &e)
{
}

// This is a barebones camera for v.01 of the engine, it will be replaced
void FighterLike::CreateCamera(u32 width, u32 height)
{
    // auto aspectRatio{static_cast<f32>(width) / static_cast<f32>(height)};
    // auto camHeight{Application::Get().GetWindowHeight() / 2};
    // auto bottom{-static_cast<i32>(camHeight)};
    // auto top{camHeight};
    // auto left{static_cast<f32>(bottom) * aspectRatio};
    // auto right{static_cast<f32>(top) * aspectRatio};
    // m_Camera = std::make_unique<OrthographicCamera>(left, right, bottom, top);
    m_Camera = std::make_unique<OrthographicCamera>(-1.f, 1.f, -1.f, 1.f);
}
