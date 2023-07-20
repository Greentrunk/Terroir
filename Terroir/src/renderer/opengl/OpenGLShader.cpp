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

#include "OpenGLShader.h"
#include "Tpch.h"
#include "core/Assert.h"
#include "math/Math.h"
#include <filesystem>

namespace Terroir
{
// Two helper functions for shader debugging
static constexpr GLenum ShaderTypeFromString(const std::string_view &type)
{
    if (type == "vertex")
        return GL_VERTEX_SHADER;
    if (type == "fragment" || type == "pixel")
        return GL_FRAGMENT_SHADER;

    TERR_ENGINE_ASSERT(false, "Unknown Shader Type!");
    return 0;
}

static constexpr const char *StringFromShaderType(const GLenum type)
{
    if (type == GL_VERTEX_SHADER)
        return "VERTEX";
    if (type == GL_FRAGMENT_SHADER)
        return "FRAGMENT";
    return "";
}

OpenGLShader::OpenGLShader(const std::string_view &name, const std::initializer_list<std::filesystem::path> &paths)

    : m_RendererID(glCreateProgram()), m_Name(name)

{
    TERR_PROFILE_FUNC;
    // List to hold shader data to be sent to preprocessor
    std::list<std::string> list;
    for (auto &path : paths)
    {
        std::string data;
        if (std::filesystem::exists(path))
        {
            ReadShaderToString(std::filesystem::path(std::filesystem::current_path() / path), data);
            list.push_back(data);
        }
        else
        {
            TERR_ENGINE_ERROR("Shader path: {} doesn't exist!", path.string());
        }
    }

    auto shaderSources = PreProcess(list);

    Compile(shaderSources);
}

OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(m_RendererID);
}

void OpenGLShader::Bind() const
{
    glUseProgram(m_RendererID);
}

void OpenGLShader::Unbind() const
{
    glUseProgram(0);
}

void OpenGLShader::UploadUniform(const char *name, const i32 i) const
{
    GLint location{glGetUniformLocation(m_RendererID, name)};
    glUniform1i(location, i);
}

void OpenGLShader::UploadUniform(const char *name, const f32 f) const
{
    GLint location{glGetUniformLocation(m_RendererID, name)};
    glUniform1f(location, f);
}

void OpenGLShader::UploadUniform(const char *name, const Vec2 &vec) const
{
    GLint location{glGetUniformLocation(m_RendererID, name)};
    glUniform2f(location, vec.x, vec.y);
}

void OpenGLShader::UploadUniform(const char *name, const Vec3 &vec) const
{
    GLint location{glGetUniformLocation(m_RendererID, name)};
    glUniform3f(location, vec.x, vec.y, vec.z);
}

void OpenGLShader::UploadUniform(const char *name, const Vec4 &vec) const
{
    GLint location{glGetUniformLocation(m_RendererID, name)};
    glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
}

void OpenGLShader::UploadUniform(const char *name, const Mat3 &matrix) const
{
    GLint location{glGetUniformLocation(m_RendererID, name)};
    glUniformMatrix3fv(location, 1, GL_FALSE, Math::Conversion::GetValuePtr(matrix));
}

void OpenGLShader::UploadUniform(const char *name, const Mat4 &matrix) const
{
    GLint location{glGetUniformLocation(m_RendererID, name)};
    glUniformMatrix4fv(location, 1, GL_FALSE, Math::Conversion::GetValuePtr(matrix));
}

void OpenGLShader::UploadUniform(const char *name, const std::span<i32> &values) const
{
    GLint location{glGetUniformLocation(m_RendererID, name)};
    glUniform1iv(location, static_cast<GLsizei>(values.size()), values.data());
}

OpenGLShader::ShaderMap OpenGLShader::PreProcess(const std::list<std::string> &srcList)
{
    TERR_PROFILE_FUNC;
    ShaderMap map;

    constexpr const char *token = "#type";
    auto tokenLength = strlen(token);

    // For every shader string that comes in
    for (const auto &src : srcList)
    {
        auto pos = src.find(token, 0);
        while (pos != std::string_view::npos)
        {
            auto eol = src.find_first_of("\r\n", pos);
            // Syntax errors
            size_t begin = pos + tokenLength + 1;
            auto type = src.substr(begin, eol - begin);
            TERR_ENGINE_ASSERT(type == "vertex" || type == "fragment" || type == "pixel", "Unknown Shader Type!");

            auto nextLinePos = src.find_first_not_of("\r\n", eol);
            pos = src.find(token, nextLinePos);

            // One shader in file or no?
            map[ShaderTypeFromString(type)] =
                src.substr(nextLinePos, pos - (nextLinePos == std::string_view::npos ? src.size() - 1 : nextLinePos));
        }
    }

    return map;
}

void OpenGLShader::Compile(const ShaderMap &shaderSources)
{
    // Store the shaders in local list for easy cleanup
    TERR_ENGINE_ASSERT(shaderSources.size() <= 6, "Only 6 shaders max supported!");
    std::array<GLuint, 6> shaders{};
    size_t index{0};

    for (auto &&[type, src] : shaderSources)
    {
        auto shader = glCreateShader(type);
        const auto csrc = src.c_str();

        glShaderSource(shader, 1, &csrc, nullptr);
        glCompileShader(shader);
        CheckCompileErrors(shader, StringFromShaderType(type));

        glAttachShader(m_RendererID, shader);

        shaders[index++] = shader;
    }

    // After all shaders have been registered link program
    glLinkProgram(m_RendererID);
    CheckCompileErrors(m_RendererID, "PROGRAM");

    // Loop again to cleanup
    for (auto &shader : shaders)
    {
        glDetachShader(m_RendererID, shader);
    }
}

void OpenGLShader::ReadShaderToString(const std::filesystem::path &path, std::string &s)
{
    TERR_PROFILE_FUNC;
    std::ifstream shaderStream;
    shaderStream.open(path);
    std::stringstream buffer;
    buffer << shaderStream.rdbuf();

    s = buffer.str();

    shaderStream.close();
}

void OpenGLShader::CheckCompileErrors(u32 shader, const std::string_view &type)
{
    TERR_PROFILE_FUNC;
    constexpr size_t logSize{1024};
    i32 success{};
    std::array<char, logSize> infoLog{};

    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, logSize, nullptr, &infoLog[0]);
            glDeleteShader(shader);
            TERR_ENGINE_ERROR("Shader Compilation Error! Type: {}", type);
            TERR_ENGINE_ERROR("Infolog: {}", infoLog.data());
            TERR_ENGINE_ASSERT(false, "Shader compilation failure");
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, logSize, nullptr, &infoLog[0]);
            glDeleteShader(shader);
            TERR_ENGINE_ERROR("Shader Linking Error! Type: {}", type);
            TERR_ENGINE_ERROR("Infolog: {}", infoLog.data());
            TERR_ENGINE_ASSERT(false, "Shader linking failure");
        }
    }
}
void OpenGLShader::SetUniform(const std::string_view &name, i32 i) const
{
    UploadUniform(name.data(), i);
}
void OpenGLShader::SetUniform(const std::string_view &name, f32 f) const
{
    UploadUniform(name.data(), f);
}
void OpenGLShader::SetUniform(const std::string_view &name, const Vec2 &vec) const
{
    UploadUniform(name.data(), vec);
}
void OpenGLShader::SetUniform(const std::string_view &name, const Vec3 &vec) const
{
    UploadUniform(name.data(), vec);
}
void OpenGLShader::SetUniform(const std::string_view &name, const Vec4 &vec) const
{
    UploadUniform(name.data(), vec);
}
void OpenGLShader::SetUniform(const std::string_view &name, const Mat3 &mat) const
{
    UploadUniform(name.data(), mat);
}
void OpenGLShader::SetUniform(const std::string_view &name, const Mat4 &mat) const
{
    UploadUniform(name.data(), mat);
}
void OpenGLShader::SetUniform(const std::string_view &name, const std::span<i32> &i) const
{
    UploadUniform(name.data(), i);
}
} // namespace Terroir
