#ifndef TERROIR_VERTEXARRAY_H
#define TERROIR_VERTEXARRAY_H

#include "buffer/IndexBuffer.h"
#include "buffer/VertexBuffer.h"
#include <memory>
namespace Terroir
{

class VertexArray
{
  public:
    virtual ~VertexArray() = default;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &) = 0;
    virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &) = 0;

    [[nodiscard]] virtual const std::vector<std::shared_ptr<VertexBuffer>> &GetVertexBuffers() const = 0;
    [[nodiscard]] virtual const std::shared_ptr<IndexBuffer> &GetIndexBuffer() const = 0;

    static std::unique_ptr<VertexArray> Create();
};
} // namespace Terroir
#endif
