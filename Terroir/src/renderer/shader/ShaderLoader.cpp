#include "ShaderLoader.h"
#include "Tpch.h"
#include <filesystem>
#include <fstream>

namespace Terroir
{
// If shaders exist, load into memory
ShaderLoader::ShaderLoader(std::filesystem::path vertexPath, std::filesystem::path fragPath)
{
    if (std::filesystem::exists(vertexPath))
    {
        ReadShaderToString(vertexPath, m_VertexShaderData);
    }
    else
    {
        TERR_ENGINE_ERROR("Vertex Shader path: {} doesn't exist!", vertexPath.string());
    }

    if (auto const fragExist{std::filesystem::exists(fragPath)}; fragExist)
    {
        ReadShaderToString(fragPath, m_FragShaderData);
    }
    else
    {
        TERR_ENGINE_ERROR("Frag Shader path: {} doesn't exist!", fragPath.string());
    }
}

void ShaderLoader::ReadShaderToString(std::filesystem::path &path, std::string &s)
{
    std::ifstream shaderStream;
    shaderStream.open(path);
    std::stringstream buffer;
    buffer << shaderStream.rdbuf();

    s = buffer.str();

    shaderStream.close();
}

} // namespace Terroir
