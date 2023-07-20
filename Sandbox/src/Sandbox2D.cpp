#include "Sandbox2D.h"
#include <imgui.h>

Sandbox2D::Sandbox2D(const std::string_view &name)
    : Layer(name), m_Texture(Texture2D::Create("Sandbox/assets/textures/gigachad.jpg"))
{
    CreateCamera(Application::Get().GetWindowWidth(), Application::Get().GetWindowHeight());
}

void Sandbox2D::OnAttach()
{
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Timestep dt)
{
    TERR_PROFILE_FUNC;

    // Reset Renderer statistics
    Renderer2D::ResetStats();

    // Clear Screen to color of choice
    RenderCommand::Clear(Color::BLACK);

    // Start draw calls
    Renderer2D::BeginScene(*m_Camera);

    // static auto rotation{0.0f};
    // rotation += dt * 100.0f;

    // const auto gigaChad = Sprite(m_Texture, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, Color::WHITE, rotation);
    // // Renderer2D::DrawSprite(gigaChad);

    // for (auto y = -5.0f; y < 5.0f; y += .5f)
    // {
    //     for (auto x = -5.0f; x < 5.0f; x += .5f)
    //     {
    //         const auto pos{Vec3{x, y, 0.0f}};
    //         const auto size{Vec2{.45f, .45f}};
    //         const auto color{Vec4{(x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, .7f}};
    //         Renderer2D::DrawRect(pos, size, color);
    //     }
    // }
    Renderer2D::EndScene();         // Finish draw calls before this
}
void Sandbox2D::OnDearImGuiRender() // Optional gui rendering
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

void Sandbox2D::OnEvent(Event &e)
{
}

// This is a barebones camera for v.01 of the engine, it will be replaced
void Sandbox2D::CreateCamera(u32 width, u32 height)
{
    // auto aspectRatio{static_cast<f32>(width) / static_cast<f32>(height)};
    // auto camHeight{Application::Get().GetWindowHeight() / 2};
    // auto bottom{-static_cast<i32>(camHeight)};
    // auto top{camHeight};
    // auto left{static_cast<f32>(bottom) * aspectRatio};
    // auto right{static_cast<f32>(top) * aspectRatio};
    // m_Camera = std::make_unique<OrthographicCamera>(left, right, bottom, top);

    m_Camera = std::make_unique<OrthographicCamera>(-1.f, 1, -1.0f, 1.0f);
}
