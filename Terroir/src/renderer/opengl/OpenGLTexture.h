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

#include "Terroir/src/renderer/texture/Texture2D.h"

namespace Terroir
{
class OpenGLTexture2D : public Texture2D
{
  public:
    OpenGLTexture2D(const std::filesystem::path &);
    virtual ~OpenGLTexture2D() override;

    [[nodiscard]] virtual u32 GetWidth() const override
    {
        return m_Width;
    }
    [[nodiscard]] virtual u32 GetHeight() const override
    {
        return m_Height;
    }

    virtual void Bind(u32 slot = 0) override;

  private:
    std::filesystem::path m_Path;
    u32 m_Width, m_Height;
    u32 m_RendererID;
};
} // namespace Terroir