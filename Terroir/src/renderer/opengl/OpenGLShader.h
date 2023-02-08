#ifndef TERROIR_OPENGLSHADER_H
#define TERROIR_OPENGLSHADER_H

#include "../shader/Shader.h"
#include "Terroir/src/core/Types.h"
#include "Terroir/src/math/Math.h"
#include <glad/glad.h>

namespace Terroir
{
// Later will open files
class OpenGLShader : public Shader
{
  public:
    using ShaderMap = std::unordered_map<GLenum, std::string>;
    // const char* used for compatibility with C-style libraries
    OpenGLShader(const std::initializer_list<std::filesystem::path> &paths = {
                     "Terroir/src/renderer/shader/DefaultVertexShader.glsl",
                     "Terroir/src/renderer/shader/DefaultFragShader.glsl"});
    ~OpenGLShader() override;
    void Bind() const;
    void Unbind() const;

    void UploadUniform(const char *, const i32 &);
    void UploadUniform(const char *, const f32 &);
    void UploadUniform(const char *, const Vec2 &);
    void UploadUniform(const char *, const Vec3 &);
    void UploadUniform(const char *, const Vec4 &);
    void UploadUniform(const char *, const Mat3 &);
    void UploadUniform(const char *, const Mat4 &);

    // debug
    inline u32 GetID()
    {
        return m_RendererID;
    }

    // Process generic shader and add its type and data to a hashmap
    ShaderMap PreProcess(const std::list<std::string> &);

    void Compile(const ShaderMap &);

  private:
    void ReadShaderToString(const std::filesystem::path &, std::string &);
    void CheckCompileErrors(u32, const std::string_view &);

    u32 m_RendererID;
};
} // namespace Terroir

#endif
