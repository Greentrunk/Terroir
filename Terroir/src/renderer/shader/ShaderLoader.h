#ifndef TERROIR_SHADERLOADER_H
#define TERROIR_SHADERLOADER_H

#include <filesystem>
#include <string>

namespace Terroir
{

class ShaderLoader
{
  public:
    ShaderLoader(std::filesystem::path, std::filesystem::path);
    ~ShaderLoader() = default;

    constexpr const char *GetVertexShader()
    {
        return m_VertexShaderData.c_str();
    }

    constexpr const char *GetFragShader()
    {
        return m_FragShaderData.c_str();
    }

  private:
    void ReadShaderToString(std::filesystem::path &, std::string &);

    std::string m_VertexShaderData;
    std::string m_FragShaderData;
};
} // namespace Terroir
#endif
