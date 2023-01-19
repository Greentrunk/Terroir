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

    [[nodiscard]] constexpr const Vec3 &GetPosition() const
    {
        return m_Position;
    }
    void SetPosition(const Vec3 &position)
    {
        m_Position = position;
        RecalculateViewMatrix();
    }

    [[nodiscard]] constexpr const f32 GetRotation() const
    {
        return m_Rotation;
    }
    void SetRotation(f32 rotation)
    {
        m_Rotation = rotation;
        RecalculateViewMatrix();
    }

    constexpr const Mat4 &GetViewProjectionMatrix()
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
