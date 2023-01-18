#ifndef TERROIR_SHADER_H
#define TERROIR_SHADER_H

#include "Terroir/src/core/Types.h"
#include <glm/glm.hpp>
#include <string>

namespace Terroir
{
// Later will open files
class Shader
{
  public:
    Shader(const std::string &, const std::string &);
    ~Shader();
    void Bind() const;
    void Unbind() const;

    void UploadUniformMat4(const std::string &, const glm::mat4 &);

    // debug
    inline u32 GetID()
    {
        return m_RendererID;
    }

  private:
    void CheckCompileErrors(u32, const std::string &);
    u32 m_RendererID;
};
} // namespace Terroir

#endif
