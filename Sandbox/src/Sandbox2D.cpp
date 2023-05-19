#include "Sandbox2D.h"


Sandbox2D::Sandbox2D(const std::string_view &name) : Layer(name)
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

    // Clear Screen to color of choice
    RenderCommand::Clear(Color::BLACK);

    // Start draw calls
    Renderer2D::BeginScene(*m_Camera);

    Renderer2D::EndScene(); // Finish draw calls before this
}
void Sandbox2D::OnDearImGuiRender() // Optional gui rendering
{
    TERR_PROFILE_FUNC;
}

void Sandbox2D::OnEvent(Event &e)
{
}

// This is a barebones camera for v.01 of the engine, it will be replaced 
void Sandbox2D::CreateCamera(u32 width, u32 height)
{
    auto aspectRatio{static_cast<f32>(width) / static_cast<f32>(height)};
    auto camHeight{Application::Get().GetWindowHeight() / 2};
    auto bottom{-static_cast<i32>(camHeight)};
    auto top{camHeight};
    auto left{static_cast<f32>(bottom) * aspectRatio};
    auto right{static_cast<f32>(top) * aspectRatio};
    m_Camera = std::make_unique<OrthographicCamera>(left, right, bottom, top);
}
