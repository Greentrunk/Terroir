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

#ifndef TERRIOR_FONTTEXTURE2D_H
#define TERRIOR_FONTTEXTURE2D_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Terroir/src/renderer/texture/Texture.h"

namespace Terroir
{
class FontTexture2D : public Texture
{
  public:
    ~FontTexture2D() override = default;

    // Get ID
    [[nodiscard]] virtual constexpr u32 GetID() const = 0;

    static std::shared_ptr<FontTexture2D> Create(u32, const FT_Face &);
};
} // namespace Terroir

#endif