#ifndef TERROIR_INDEXBUFFER_H
#define TERROIR_INDEXBUFFER_H

#include "Terroir/src/core/Types.h"
#include <memory>

namespace Terroir
{

class IndexBuffer
{
  public:
    virtual ~IndexBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    [[nodiscard]] virtual u32 GetIndexCount() const = 0;

    static std::unique_ptr<IndexBuffer> Create(u32 *, u32);
};
} // namespace Terroir

#endif // !TERROIR_INDEXBUFFER_H
