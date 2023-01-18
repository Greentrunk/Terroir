#ifndef TERROIR_ORTHOGRAPHICCAMERA_H
#define TERROIR_ORTHOGRAPHICCAMERA_H

#include "Terroir/src/core/Types.h"
#include <glm/glm.hpp>

namespace Terroir
{

class OrthographicCamera
{

  public:
    OrthographicCamera(f32, f32, f32, f32);

    [[nodiscard]] constexpr const glm::vec3 &GetPosition() const
    {
        return m_Position;
    }
    void SetPosition(const glm::vec3 &position)
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

    glm::mat4 constexpr const &GetViewProjectionMatrix()
    {
        return m_ViewProjectionMatrix;
    }

  private:
    void RecalculateViewMatrix();

    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ViewProjectionMatrix;

    glm::vec3 m_Position{0.0f};
    f32 m_Rotation{0.0f};
};

} // namespace Terroir
#endif
