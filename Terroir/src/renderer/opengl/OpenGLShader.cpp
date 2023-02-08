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

OpenGLShader::OpenGLShader(const std::initializer_list<std::filesystem::path> &paths)

    : m_RendererID(glCreateProgram())

{
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

OpenGLShader::ShaderMap OpenGLShader::PreProcess(const std::list<std::string> &srcList)
{
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
    std::list<GLuint> shaders;

    for (auto &&[type, src] : shaderSources)
    {
        auto shader = glCreateShader(type);
        const auto csrc = src.c_str();

        glShaderSource(shader, 1, &csrc, nullptr);
        glCompileShader(shader);
        CheckCompileErrors(shader, StringFromShaderType(type));

        glAttachShader(m_RendererID, shader);

        shaders.push_back(shader);
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
    std::ifstream shaderStream;
    shaderStream.open(path);
    std::stringstream buffer;
    buffer << shaderStream.rdbuf();

    s = buffer.str();

    shaderStream.close();
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
