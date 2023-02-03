#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Terroir/src/core/Types.h"

namespace Terroir
{
class Texture
{
  public:
    virtual ~Texture() = default;

    [[nodiscard]] virtual u32 GetWidth() const = 0;
    [[nodiscard]] virtual u32 GetHeight() const = 0;

    virtual void Bind(u32 slot = 0) = 0;
};
} // namespace Terroir

#endif // __TEXTURE_H__