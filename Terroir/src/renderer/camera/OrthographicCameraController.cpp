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

#include "OrthographicCameraController.h"
#include "Terroir/src/core/KeyCodes.h"
#include "Terroir/src/platform/Input.h"
#include "Tpch.h"

namespace Terroir
{
OrthographicCameraController::OrthographicCameraController(f32 aspectRatio, bool rotation)
    : m_AspectRatio(aspectRatio),
      m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
      m_Rotation(rotation)
{
}

void OrthographicCameraController::OnUpdate(Timestep dt)
{
    if (Input::IsKeyPressed(TERR_KEY_A))
    {
        m_CameraPosition.x -= m_CameraTranslationVelocity * dt;
    }

    if (Input::IsKeyPressed(TERR_KEY_D))
    {
        m_CameraPosition.x += m_CameraTranslationVelocity * dt;
    }

    if (Input::IsKeyPressed(TERR_KEY_S))
    {
        m_CameraPosition.y -= m_CameraTranslationVelocity * dt;
    }
    if (Input::IsKeyPressed(TERR_KEY_W))
    {
        m_CameraPosition.y += m_CameraTranslationVelocity * dt;
    }

    if (m_Rotation)
    {
        // Do rotations
        m_Camera.SetRotation(m_CameraRotation * m_CameraRotationVelocity);
    }

    m_Camera.SetPosition(m_CameraPosition);
}

void OrthographicCameraController::OnEvent(Event &e)
{
    EventDispatch dispatcher(e);
    dispatcher.Dispatch<MouseScrolledEvent>(TERR_BIND_EVENT_LAMBDA(OrthographicCameraController::OnMouseScrolled));
    dispatcher.Dispatch<WindowResizeEvent>(TERR_BIND_EVENT_LAMBDA(OrthographicCameraController::OnWindowResized));
}

bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent &e)
{
    m_ZoomLevel -= e.GetYOffset() * 0.25f;
    m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    return false;
}

bool OrthographicCameraController::OnWindowResized(WindowResizeEvent &e)
{
    m_AspectRatio = static_cast<f32>(e.GetWidth()) / static_cast<f32>(e.GetHeight());
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    return false;
}
} // namespace Terroir
