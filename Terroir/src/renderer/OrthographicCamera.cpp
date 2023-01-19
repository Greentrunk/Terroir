#include "OrthographicCamera.h"
#include "Tpch.h"
#include "math/Math.h"

namespace Terroir
{
using namespace Math;
OrthographicCamera::OrthographicCamera(f32 left, f32 right, f32 bottom, f32 top)
    : m_ProjectionMatrix(Transform::Ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)

{
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void OrthographicCamera::RecalculateViewMatrix()
{
    Mat4 transform{Transform::Translate(Mat4(1.0f), m_Position) *
                   Transform::Rotate(Mat4(1.0f), Conversion::ToRadians(m_Rotation), Vec3(0, 0, 1))};

    m_ViewMatrix = Transform::Inverse(transform);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

} // namespace Terroir
