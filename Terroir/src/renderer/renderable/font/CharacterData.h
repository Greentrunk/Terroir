#ifndef TERROIR_CHARACTERDATA_H
#define TERROIR_CHARACTERDATA_H

#include "Terroir/src/core/Types.h"
#include "Terroir/src/math/Math.h"
#include "Terroir/src/renderer/texture/FontTexture2D.h"

namespace Terroir
{
class CharacterData
{
  public:
    // Constructor
    CharacterData(std::shared_ptr<FontTexture2D> texture, Vec2 size, Vec2 bearing, u32 advance)
        : m_Texture(std::move(texture)), m_Size(size), m_Bearing(bearing), m_Advance(advance)
    {
    }

    // Getters
    [[nodiscard]] constexpr const std::shared_ptr<FontTexture2D> &GetTexture() const
    {
        return m_Texture;
    }

    [[nodiscard]] constexpr const Vec2 &GetSize() const
    {
        return m_Size;
    }

    [[nodiscard]] constexpr const Vec2 &GetBearing() const
    {
        return m_Bearing;
    }

    [[nodiscard]] constexpr u32 GetAdvance() const
    {
        return m_Advance;
    }

  private:
    std::shared_ptr<FontTexture2D> m_Texture;
    Vec2 m_Size;
    Vec2 m_Bearing;
    u32 m_Advance;
};
} // namespace Terroir

#endif