#include "OpenGLShader.h"
#include "Tpch.h"
#include "core/Assert.h"
#include "glad/glad.h"
#include "math/Math.h"
#include <filesystem>
#include <glm/gtc/type_ptr.hpp>

namespace Terroir
{
OpenGLShader::OpenGLShader(const char *vertexPath, const char *fragPath)

    : m_RendererID(glCreateProgram()),
      m_ShaderLoader(std::filesystem::path(std::filesystem::current_path() / vertexPath),
                     std::filesystem::path(std::filesystem::current_path() / fragPath))
{
    auto const vertexShader = m_ShaderLoader.GetVertexShader();
    auto const fragShader = m_ShaderLoader.GetFragShader();

    u32 vertex{}, fragment{};
    vertex = glCreateShader(GL_VERTEX_SHADER);

    // Vertex shader
    glShaderSource(vertex, 1, &vertexShader, nullptr);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");

    // Frag shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragShader, nullptr);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");

    // Shader program
    glAttachShader(m_RendererID, vertex);
    glAttachShader(m_RendererID, fragment);
    glLinkProgram(m_RendererID);
    CheckCompileErrors(m_RendererID, "PROGRAM");

    // Cleanup
    glDetachShader(m_RendererID, vertex);
    glDetachShader(m_RendererID, fragment);
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

void OpenGLShader::UploadUniform(const char *name, const Mat4 &matrix)
{
    GLint location{glGetUniformLocation(m_RendererID, name)};
    glUniformMatrix4fv(location, 1, GL_FALSE, Math::Conversion::GetValuePtr(matrix));
}

void OpenGLShader::UploadUniform(const char *name, const i32 &i)
{
    GLint location{glGetUniformLocation(m_RendererID, name)};
    glUniform1i(location, i);
}

void OpenGLShader::UploadUniform(const char *name, const f32 &f)
{
    GLint location{glGetUniformLocation(m_RendererID, name)};
    glUniform1f(location, f);
}

void OpenGLShader::UploadUniform(const char *name, const Vec2 &vec)
{
    GLint location{glGetUniformLocation(m_RendererID, name)};
    glUniform2f(location, vec.x, vec.y);
}

void OpenGLShader::UploadUniform(const char *name, const Vec3 &vec)
{
    GLint location{glGetUniformLocation(m_RendererID, name)};
    glUniform3f(location, vec.x, vec.y, vec.z);
}

void OpenGLShader::UploadUniform(const char *name, const Vec4 &vec)
{
    GLint location{glGetUniformLocation(m_RendererID, name)};
    glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
}
void OpenGLShader::UploadUniform(const char *, const Mat3 &)
{
}
void OpenGLShader::CheckCompileErrors(u32 shader, const std::string_view &type)
{
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
} // namespace Terroir
