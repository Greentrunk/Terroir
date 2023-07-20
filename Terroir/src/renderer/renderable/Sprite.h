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

#ifndef TERROIR_SPRITE_H
#define TERROIR_SPRITE_H

#include "Terroir/src/math/Math.h"
#include "Terroir/src/renderer/renderable/Renderable2D.h"
#include "Terroir/src/renderer/texture/Texture2D.h"

namespace Terroir
{

class Sprite : public Renderable2D
{
  public:
    // Contstructor with texture and all other values
    explicit Sprite(std::shared_ptr<Texture2D> texture, const Vec2 &spriteIndex = {0.0f, 0.0f},
                     const Vec2 &cellSize = {0.0f, 0.0f}, const Vec2 &spriteSize = {1.0f, 1.0f}, const Vec3 &position = {0.0f, 0.0f, 0.0f},
                    const Vec2 &size = {1.0f, 1.0f}, const Vec4 &color = {1.0f, 1.0f, 1.0f, 1.0f}, f32 rotation = 0.0f,
                    const Vec4 &tintColor = {1.0f, 1.0f, 1.0f, 1.0f}, const f32 tilingFactor = 1.0f)
        : Renderable2D(position, size, color, rotation), m_Texture(texture)
    {
        const auto texWidth{texture->GetWidth()};
        const auto texHeight{texture->GetHeight()};

        auto min{Vec2((spriteIndex.x * cellSize.x) / texWidth, (spriteIndex.y * cellSize.y) / texHeight)};
        auto max{
            Vec2(((spriteIndex.x + spriteSize.x) * cellSize.x) / texWidth, ((spriteIndex.y + spriteSize.y) * cellSize.y) / texHeight)};

        // if min and max were defaulty constructed set textCoords to base texture
        if (min == Vec2(0.0f, 0.0f) && max == Vec2(0.0f, 0.0f))
        {
            m_TexCoords[0] = {0.0f, 0.0f};
            m_TexCoords[1] = {1.0f, 0.0f};
            m_TexCoords[2] = {1.0f, 1.0f};
            m_TexCoords[3] = {0.0f, 1.0f};
        }
        else
        {
            m_TexCoords[0] = {min.x, min.y};
            m_TexCoords[1] = {max.x, min.y};
            m_TexCoords[2] = {max.x, max.y};
            m_TexCoords[3] = {min.x, max.y};
        }

        m_TintColor = tintColor;
        m_TilingFactor = tilingFactor;
    }

    [[nodiscard]] const std::shared_ptr<Texture2D> &GetTexture() const
    {
        return m_Texture;
    }

    [[nodiscard]] constexpr const Vec4 &GetTintColor() const
    {
        return m_TintColor;
    }

    [[nodiscard]] constexpr f32 GetTilingFactor() const
    {
        return m_TilingFactor;
    }

    [[nodiscard]] constexpr const std::array<Vec2, 4> &GetTexCoords() const
    {
        return m_TexCoords;
    }

  private:
    std::shared_ptr<Texture2D> m_Texture;
    Vec4 m_TintColor;
    f32 m_TilingFactor;
    std::array<Vec2, 4> m_TexCoords;
};

} // namespace Terroir

#endif // TERROIR_SPRITE_H
