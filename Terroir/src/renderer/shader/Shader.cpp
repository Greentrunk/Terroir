#include "Shader.h"
#include "Tpch.h"
#include "core/Assert.h"
#include "glad/glad.h"
#include "math/Math.h"
#include <glm/gtc/type_ptr.hpp>

namespace Terroir
{
Shader::Shader(const char *vertexShader, const char *fragShader) : m_RendererID(glCreateProgram())
{

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

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::UploadUniformMat4(const char *name, const Mat4 &matrix)
{
    GLint location{glGetUniformLocation(m_RendererID, name)};
    glUniformMatrix4fv(location, 1, GL_FALSE, Math::Conversion::GetValuePtr(matrix));
}

void Shader::CheckCompileErrors(u32 shader, const std::string_view &type)
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
