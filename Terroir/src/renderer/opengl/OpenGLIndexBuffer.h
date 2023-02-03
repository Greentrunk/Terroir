#ifndef TERROIR_OPENGLINDEXBUFFER_H
#define TERROIR_OPENGLINDEXBUFFER_H

#include "Terroir/src/renderer/buffer/IndexBuffer.h"

namespace Terroir
{

class OpenGLIndexBuffer : public IndexBuffer
{
  public:
    OpenGLIndexBuffer(u32 *, u32);
    ~OpenGLIndexBuffer() override;

    void Bind() const override;
    void Unbind() const override;

    [[nodiscard]] u32 GetIndexCount() const override
    {
        return m_Count;
    }

  private:
    u32 m_RendererId{};
    u32 m_Count;
};
} // namespace Terroir

#endif // !TERROIR_OPENGLVERTEXBUFFER_H
