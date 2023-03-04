////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Christopher J. Pohl 2023 to Present  All Rights Reserved.
//
// This file is part of TERROIR ENGINE:
// This is free software as described by the Apache 2.0 License
//
// The above copyright notice shall be included in all portions of this software
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#ifndef TERROIR_OPENGLSHADER_H
#define TERROIR_OPENGLSHADER_H

#include "../shader/Shader.h"
#include "Terroir/src/core/Types.h"
#include "Terroir/src/math/Math.h"
#include <glad/glad.h>
#include <list>

namespace Terroir
{
// Later will open files
class OpenGLShader : public Shader
{
  public:
    using ShaderMap = std::unordered_map<GLenum, std::string>;
    // const char* used for compatibility with C-style libraries
    explicit OpenGLShader(const std::string_view &name = "Default",
                          const std::initializer_list<std::filesystem::path> &paths = {
                              "Terroir/src/renderer/shader/DefaultVertexShader.glsl",
                              "Terroir/src/renderer/shader/DefaultFragShader.glsl"});
    ~OpenGLShader() override;
    void Bind() const override;
    void Unbind() const override;

    // High level uniforms
    void SetUniform(const std::string_view &, i32) const override;
    void SetUniform(const std::string_view &, f32) const override;
    void SetUniform(const std::string_view &, const Vec2 &) const override;
    void SetUniform(const std::string_view &, const Vec3 &) const override;
    void SetUniform(const std::string_view &, const Vec4 &) const override;
    void SetUniform(const std::string_view &, const Mat3 &) const override;
    void SetUniform(const std::string_view &, const Mat4 &) const override;

    // OpenGL specific uniforms
    void UploadUniform(const char *, i32) const;
    void UploadUniform(const char *, f32) const;
    void UploadUniform(const char *, const Vec2 &) const;
    void UploadUniform(const char *, const Vec3 &) const;
    void UploadUniform(const char *, const Vec4 &) const;
    void UploadUniform(const char *, const Mat3 &) const;
    void UploadUniform(const char *, const Mat4 &) const;

    [[nodiscard]] constexpr const std::string &GetName() const override
    {
        return m_Name;
    }

    // debug
    inline u32 GetID()
    {
        return m_RendererID;
    }

    // Process generic shader and add its type and data to a hashmap
    // When a max shader size will be decided, this will be turned into an array, not list
    ShaderMap PreProcess(const std::list<std::string> &);

    void Compile(const ShaderMap &);

  private:
    static void ReadShaderToString(const std::filesystem::path &, std::string &);
    void CheckCompileErrors(u32, const std::string_view &) override;

    u32 m_RendererID;
    std::string m_Name;
};
} // namespace Terroir

#endif
