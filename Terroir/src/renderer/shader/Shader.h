#ifndef TERROIR_SHADER_H
#define TERROIR_SHADER_H

#include "ShaderLoader.h"
#include "Terroir/src/core/Types.h"
#include "Terroir/src/math/Math.h"
#include <string>

namespace Terroir
{
// Later will open files
class Shader
{
  public:
    // const char* used for compatibility with C-style libraries
    Shader(const char *vertexPath = "DefaultVertexShader.glsl", const char *fragPath = "DefaultFragShader.glsl");
    ~Shader();
    void Bind() const;
    void Unbind() const;

    void UploadUniformMat4(const char *, const Mat4 &);

    // debug
    inline u32 GetID()
    {
        return m_RendererID;
    }

  private:
    void CheckCompileErrors(u32, const std::string_view &);
    u32 m_RendererID;
    // This will be generic when using other shader languages
    ShaderLoader m_ShaderLoader;
};
} // namespace Terroir

#endif
