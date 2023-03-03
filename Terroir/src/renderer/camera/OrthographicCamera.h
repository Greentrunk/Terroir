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

#ifndef TERROIR_ORTHOGRAPHICCAMERA_H
#define TERROIR_ORTHOGRAPHICCAMERA_H

#include "Terroir/src/core/Types.h"
#include "Terroir/src/math/Math.h"

namespace Terroir
{

class OrthographicCamera
{

  public:
    OrthographicCamera(f32, f32, f32, f32);
    void SetProjection(f32, f32, f32, f32);

    [[nodiscard]] constexpr const Vec3 &GetPosition() const
    {
        return m_Position;
    }
    void SetPosition(const Vec3 &position)
    {
        m_Position = position;
        RecalculateViewMatrix();
    }

    [[nodiscard]] constexpr f32 GetRotation() const
    {
        return m_Rotation;
    }

    void SetRotation(f32 rotation)
    {
        m_Rotation = rotation;
        RecalculateViewMatrix();
    }

    [[nodiscard]] constexpr const Mat4 &GetViewProjectionMatrix() const
    {
        return m_ViewProjectionMatrix;
    }

  private:
    void RecalculateViewMatrix();

    Mat4 m_ProjectionMatrix;
    Mat4 m_ViewMatrix;
    Mat4 m_ViewProjectionMatrix;

    Vec3 m_Position{0.0f};
    f32 m_Rotation{0.0f};
};

} // namespace Terroir
#endif
