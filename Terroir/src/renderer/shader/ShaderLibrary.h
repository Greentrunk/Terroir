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

#ifndef __SHADERLIBRARY_H__
#define __SHADERLIBRARY_H__

#include "Shader.h"

namespace Terroir
{
// Singleton that holds registered rendering shaders
class ShaderLibrary
{
  public:
    using SharedShader = std::shared_ptr<Shader>;

    // Add to library
    void Add(const SharedShader &);

    // Default name is "Default"
    SharedShader Load();

    // Key names defaulted from filename
    SharedShader Load(const std::string_view &, const std::initializer_list<std::filesystem::path> &);

    SharedShader Get(const std::string &name = "Default");

    bool Exists(const std::string &name) const;

  private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
};
} // namespace Terroir
#endif // __SHADERLIBRARY_H__