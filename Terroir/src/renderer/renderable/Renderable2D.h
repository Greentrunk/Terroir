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

#ifndef TERROIR_RENDERABLE2D_H
#define TERROIR_RENDERABLE2D_H

#include "Terroir/src/math/Math.h"

namespace Terroir
{

class Renderable2D
{
  public:
    // Constrctor that takes in a position, size, color, and rotation
    Renderable2D(const Vec3 &position, const Vec2 &size, const Vec4 &color, f32 rotation = 0.0f)
        : m_Position(position), m_Size(size), m_Color(color), m_Rotation(rotation)
    {
    }

    // constexpr function that returns a the total transform matrix
    [[nodiscard]] Mat4 GetTransform() const noexcept
    {
        // Set rotation if default value isn't used
        Mat4 rotate{1.0f};
        if (m_Rotation != 0.0f)
        {
            rotate = Math::Transform::Rotate(Mat4(1.0f), m_Rotation, {0.0f, 0.0f, 1.0f});
        }
        return Math::Transform::Translate(Mat4(1.0f), m_Position) * rotate *
               Math::Transform::Scale(Mat4(1.0f), {m_Size.x, m_Size.y, 1.0f});
    }

  private:
    Vec3 m_Position;
    Vec2 m_Size;
    Vec4 m_Color;
    f32 m_Rotation;
};

} // namespace Terroir

#endif // TERROIR_RENDERABLE2D_H
