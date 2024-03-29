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

#ifndef __TEXTURE2D_H__
#define __TEXTURE2D_H__

#include "Texture.h"
#include <filesystem>
#include <memory>

namespace Terroir
{
class Texture2D : public Texture
{
  public:
    ~Texture2D() override = default;

    static std::shared_ptr<Texture2D> Create(u32, u32);
    static std::shared_ptr<Texture2D> Create(const std::filesystem::path &);

    // Get ID
    [[nodiscard]] virtual constexpr u32 GetID() const = 0;
};

} // namespace Terroir
#endif // __TEXTURE2D_H__