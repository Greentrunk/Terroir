#include "ShaderLibrary.h"
#include "Terroir/src/core/Assert.h"

namespace Terroir
{
void ShaderLibrary::Add(const SharedShader &shader)
{
    auto &name{shader->GetName()};
    TERR_ENGINE_ASSERT(!Exists(name), "Shader already exists!");
    m_Shaders[name] = shader;
}

ShaderLibrary::SharedShader ShaderLibrary::Load()
{
    auto shader = Shader::Create();
    Add(shader);
    return shader;
}

ShaderLibrary::SharedShader ShaderLibrary::Load(const std::string_view &name,
                                                const std::initializer_list<std::filesystem::path> &paths)
{
    auto shader = Shader::Create(name, paths);
    Add(shader);
    return shader;
}

ShaderLibrary::SharedShader ShaderLibrary::Get(const std::string &name)
{
    TERR_ENGINE_ASSERT(Exists(name), "Shader not found in library!");
    return m_Shaders[name];
}

bool ShaderLibrary::Exists(const std::string &name) const
{
    return m_Shaders.find(name) != m_Shaders.end();
}
} // namespace Terroir