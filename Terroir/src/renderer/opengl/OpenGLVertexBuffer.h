#ifndef TERROIR_OPENGLVERTEXBUFFER_H
#define TERROIR_OPENGLVERTEXBUFFER_H

#include "Terroir/src/renderer/buffer/VertexBuffer.h"
namespace Terroir
{

class OpenGLVertexBuffer : public VertexBuffer
{
  public:
    OpenGLVertexBuffer(f32 *, u32);
    ~OpenGLVertexBuffer() override;

    void Bind() const override;
    void Unbind() const override;

    void SetLayout(const BufferLayout &) override;
    [[nodiscard]] constexpr const BufferLayout &GetLayout() const override
    {
        return m_Layout;
    }

  private:
    u32 m_RendererId{};
    BufferLayout m_Layout{};
};
} // namespace Terroir

#endif // !TERROIR_OPENGLVERTEXBUFFER_H
