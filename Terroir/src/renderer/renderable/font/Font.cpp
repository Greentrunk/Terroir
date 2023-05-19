#include "Font.h"
#include "Tpch.h"

#include "renderer/texture/FontTexture2D.h"
#include <glad/glad.h>

namespace Terroir
{

Font::Font() : Renderable2D({0, 0, 0}, {0, 0}, {0, 0, 0, 0}, 0)
{
    // Init Freetype
    if (FT_Init_FreeType(&m_Library))
    {
        TERR_ENGINE_ERROR("Freetype failed to initialize");
    }

    // Test font
    FT_Face face;
    if (FT_New_Face(m_Library, "Terroir/src/renderer/renderable/font/Roboto-Medium.ttf", 0, &face))
    {
        TERR_ENGINE_ERROR("Failed to load font");
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    {
        TERR_ENGINE_ERROR("Failed to load glyph");
    }

    // Create textures and add to map for ASCII range
    for (auto c = 0; c < 128; c++)
    {
        // Texture
        const auto charTexture = FontTexture2D::Create(c, face);

        // Add to map
        auto characterData{CharacterData{charTexture,
                                         {face->glyph->bitmap.width, face->glyph->bitmap.rows},
                                         {face->glyph->bitmap_left, face->glyph->bitmap_top},
                                         static_cast<u32>(face->glyph->advance.x)}};
        m_Characters.insert(std::pair<char, CharacterData>(c, characterData));
    }

    // Cleanup face
    FT_Done_Face(face);
}

Font::~Font()
{
    FT_Done_FreeType(m_Library);
}

} // namespace Terroir
