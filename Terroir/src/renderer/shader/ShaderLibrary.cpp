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