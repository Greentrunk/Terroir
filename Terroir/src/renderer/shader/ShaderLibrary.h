#ifndef __SHADERLIBRARY_H__
#define __SHADERLIBRARY_H__

#include "Shader.h"

namespace Terroir
{
// Singleton that holds registered rendering shaders
class ShaderLibrary
{
  public:
    using SharedShader = std::shared_ptr<Shader>;

    // Add to library
    void Add(const SharedShader &);

    // Default name is "Default"
    SharedShader Load();

    // Key names defaulted from filename
    SharedShader Load(const std::string_view &, const std::initializer_list<std::filesystem::path> &);

    SharedShader Get(const std::string &);

    bool Exists(const std::string &name) const;

  private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
};
} // namespace Terroir
#endif // __SHADERLIBRARY_H__