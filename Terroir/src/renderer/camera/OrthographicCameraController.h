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

#ifndef __ORTHOGRAPHICCAMERACONTROLLER_H__
#define __ORTHOGRAPHICCAMERACONTROLLER_H__

#include "OrthographicCamera.h"
#include "Terroir/src/core/Timestep.h"
#include "Terroir/src/core/event/MouseEvent.h"
#include "Terroir/src/core/event/WindowEvent.h"

namespace Terroir
{
class OrthographicCameraController
{
  public:
    // Takes in aspect ratio
    explicit OrthographicCameraController(f32, bool rotation = false);

    [[nodiscard]] constexpr OrthographicCamera &GetCamera()
    {
        return m_Camera;
    }
    [[nodiscard]] constexpr const OrthographicCamera &GetCamera() const
    {
        return m_Camera;
    }

    constexpr void SetZoomLevel(f32 level)
    {
        m_ZoomLevel = level;
    }

    [[nodiscard]] constexpr f32 GetZoomLevel() const
    {
        return m_ZoomLevel;
    }

    void OnUpdate(Timestep);
    void OnEvent(Event &);

  private:
    bool OnMouseScrolled(MouseScrolledEvent &);
    bool OnWindowResized(WindowResizeEvent &);

    f32 m_AspectRatio;
    f32 m_ZoomLevel{1.0f};
    OrthographicCamera m_Camera;

    bool m_Rotation;
    Vec3 m_CameraPosition{0.0f, 0.0f, 0.0f};
    f32 m_CameraRotation{0.0f};

    f32 m_CameraTranslationVelocity{1.0f}, m_CameraRotationVelocity{1.0f};
};
} // namespace Terroir
#endif // __ORTHOGRAPHICCAMERACONTROLLER_H__