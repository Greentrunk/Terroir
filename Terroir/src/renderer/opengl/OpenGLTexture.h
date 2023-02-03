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

    virtual void Bind();

  private:
    std::filesystem::path m_Path;
    u32 m_Width, m_Height;
    u32 m_RendererID;
};
} // namespace Terroir