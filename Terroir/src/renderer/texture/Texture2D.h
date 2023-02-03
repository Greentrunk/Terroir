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
    static std::unique_ptr<Texture2D> Create(const std::filesystem::path &);
};

} // namespace Terroir
#endif // __TEXTURE2D_H__