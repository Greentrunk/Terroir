#ifndef TERROIR_OPENGLVERTEXARRAY_H
#define TERROIR_OPENGLVERTEXARRAY_H

#include "../VertexArray.h"
#include "Terroir/src/core/Types.h"
#include <vector>

namespace Terroir
{
class OpenGLVertexArray : public VertexArray
{
  public:
    OpenGLVertexArray();
    ~OpenGLVertexArray() override;

    void Bind() override;
    void Unbind() override;

    void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &) override;
    void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &) override;

    [[nodiscard]] constexpr const std::vector<std::shared_ptr<VertexBuffer>> &GetVertexBuffers() const override
    {
        return m_VertexBuffers;
    }
    [[nodiscard]] constexpr const std::shared_ptr<IndexBuffer> &GetIndexBuffer() const override
    {
        return m_IndexBuffer;
    }

  private:
    u32 m_RendererId{};
    std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
};

} // namespace Terroir
#endif // !TERROIR_OPENGLVERTEXARRAY_H
