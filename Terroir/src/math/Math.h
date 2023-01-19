#ifndef TERROIR_MATH_H
#define TERROIR_MATH_H

#include "Terroir/src/core/Types.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Wrapper for glm math library to be used in Terroir engine
namespace Terroir
{

// Basic types
using Vec3 = glm::vec3;
using Vec4 = glm::vec4;
using Mat4 = glm::mat4;

// Transforms
namespace Math
{
namespace Transform
{
inline Mat4 Ortho(const f32 left, const f32 right, const f32 bottom, const f32 top, const f32 zNear, const f32 zFar)
{
    return glm::ortho(left, right, bottom, top, zNear, zFar);
}

inline Mat4 Translate(const Mat4 &m, const Vec3 &v)
{
    return glm::translate(m, v);
}

inline Mat4 Rotate(const Mat4 &m, const f32 angle, const Vec3 &v)
{
    return glm::rotate(m, angle, v);
}

inline Mat4 Inverse(const Mat4 &m)
{
    return glm::inverse(m);
}

} // namespace Transform

namespace Conversion
{

inline f32 ToRadians(const f32 degrees)
{
    return glm::radians(degrees);
}

template <typename genType> typename genType::value_type constexpr const *GetValuePtr(genType const &g)
{
    return glm::value_ptr(g);
}

} // namespace Conversion

} // namespace Math

} // namespace Terroir

#endif
