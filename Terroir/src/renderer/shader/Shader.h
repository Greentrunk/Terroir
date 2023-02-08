#ifndef TERROIR_SHADER_H
#define TERROIR_SHADER_H

#include "Terroir/src/core/Types.h"

namespace Terroir
{
// Later will open files
class Shader
{
  public:
    // const char* used for compatibility with C-style libraries
    virtual ~Shader() = default;
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    [[nodiscard]] virtual constexpr const std::string& GetName() const = 0;

    static std::shared_ptr<Shader> Create();
    // Pass a list of shader paths
    static std::shared_ptr<Shader> Create(const std::string_view&, const std::initializer_list<std::filesystem::path> &);

  private:
    virtual void CheckCompileErrors(u32, const std::string_view &) = 0;
};
} // namespace Terroir

#endif
