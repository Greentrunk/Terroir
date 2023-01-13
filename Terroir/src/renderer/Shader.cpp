#include "Shader.h"
#include "Tpch.h"
#include "core/Assert.h"
#include "glad/glad.h"

namespace Terroir
{
Shader::Shader(const std::string &vertexShader, const std::string &fragShader) : m_ID(glCreateProgram())
{
    const auto vShader = vertexShader.c_str();
    const auto fShader = fragShader.c_str();

    u32 vertex{}, fragment{};
    vertex = glCreateShader(GL_VERTEX_SHADER);

    // Vertex shader
    glShaderSource(vertex, 1, &vShader, nullptr);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");

    // Frag shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShader, nullptr);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");

    // Shader program
    glAttachShader(m_ID, vertex);
    glAttachShader(m_ID, fragment);
    glLinkProgram(m_ID);
    CheckCompileErrors(m_ID, "PROGRAM");

    // Cleanup
    glDetachShader(m_ID, vertex);
    glDetachShader(m_ID, fragment);
}

Shader::~Shader()
{
    glDeleteProgram(m_ID);
}

void Shader::Bind() const
{
    glUseProgram(m_ID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::CheckCompileErrors(u32 shader, const std::string &type)
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
