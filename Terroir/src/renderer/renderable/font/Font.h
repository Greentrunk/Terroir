#ifndef TERROIR_FONT_H
#define TERROIR_FONT_H

#include "Terroir/src/renderer/renderable/Renderable2D.h"
#include "Terroir/src/renderer/renderable/font/CharacterData.h"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Terroir
{

class Font : public Renderable2D
{
  public:
    explicit Font();

    ~Font();

    // void Render(f32, f32, f32, Vec3, const std::string &);

    [[nodiscard]] constexpr FT_Library GetLibrary() const
    {
        return m_Library;
    }

    // Get character from m_Characters
    [[nodiscard]] CharacterData GetCharacter(char c) const
    {
        return m_Characters.at(c);
    }

  private:
    FT_Library m_Library;
    std::unordered_map<char, CharacterData> m_Characters;
};

} // namespace Terroir

#endif