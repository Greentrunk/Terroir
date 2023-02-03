#ifndef TERROIR_OPENGLSHADER_H
#define TERROIR_OPENGLSHADER_H

#include "../shader/Shader.h"
#include "../shader/ShaderLoader.h"
#include "Terroir/src/core/Types.h"
#include "Terroir/src/math/Math.h"

namespace Terroir
{
// Later will open files
class OpenGLShader : public Shader
{
  public:
    // const char* used for compatibility with C-style libraries
    OpenGLShader(const char *vertexPath = "Terroir/src/renderer/shader/DefaultVertexShader.glsl", const char *fragPath = "Terroir/src/renderer/shader/DefaultFragShader.glsl");
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

  private:
    void CheckCompileErrors(u32, const std::string_view &);
    u32 m_RendererID;
    // This will be generic when using other shader languages
    ShaderLoader m_ShaderLoader;
};
} // namespace Terroir

#endif
