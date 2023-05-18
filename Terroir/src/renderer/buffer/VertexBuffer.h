#ifndef TERROIR_VERTEXBUFFER_H
#define TERROIR_VERTEXBUFFER_H

#include "Terroir/src/core/Types.h"
#include "Terroir/src/renderer/buffer/BufferLayout.h"
#include <memory>

namespace Terroir
{

class VertexBuffer
{
  public:
    virtual ~VertexBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void SetLayout(const BufferLayout &) = 0;
    [[nodiscard]] virtual const BufferLayout &GetLayout() const = 0;

    // Get ID
    [[nodiscard]] virtual constexpr u32 GetID() const = 0;

    virtual void SetBufferSubData(u32,f32*) = 0;

    static std::shared_ptr<VertexBuffer> Create(f32 *, u32, bool dyn = false);
};
} // namespace Terroir

#endif // !TERROIR_VERTEXBUFFER_H
