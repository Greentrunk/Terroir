////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Christopher J. Pohl 2023 to Present  All Rights Reserved.
//
// This file is part of TERROIR ENGINE:
// This is free software as described by the Apache 2.0 License
//
// The above copyright notice shall be included in all portions of this software
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#include "Sandbox2D.h"
#include "filesystem"
#include <imgui.h>

Sandbox2D::Sandbox2D(const std::string_view &name) : Layer(name), m_CameraController(1280.0f / 720.0f, false)
{
}

void Sandbox2D::OnAttach()
{
    m_GreenTrunkTexture = Texture2D::Create(std::filesystem::path("Sandbox/assets/textures/logo.png"));
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Timestep dt)
{
    TERR_PROFILE_FUNC;

    // Update camera
    m_CameraController.OnUpdate(dt);

    // Clear Screen to color
    RenderCommand::Clear({.1, 1, .6, 1});

    // Draw whatever you want
    Renderer2D::BeginScene(m_CameraController.GetCamera());
    Sprite greenTrunk(m_GreenTrunkTexture, {0.0f, 0.0f, -0.1f}, {3.0f, 3.0f}, {1.0f, 0.0f, 0.0f, 1.0f});
    Renderer2D::DrawSprite(greenTrunk);
    Renderer2D::DrawRect({-1.0f, 0.0}, {0.3, 0.3f}, {0.1f, 0.8f, 0.3f, 1.0f});
    Renderer2D::DrawRect({0.5f, -0.5}, {0.5, 0.3f}, {1.0f, 0.8f, 0.3f, 1.0f});
    Renderer2D::EndScene();
}
void Sandbox2D::OnDearImGuiRender()
{
    TERR_PROFILE_FUNC;

    ImGui::Begin("Settings");
    ImGui::End();
}
void Sandbox2D::OnEvent(Event &e)
{
    m_CameraController.OnEvent(e);
}
