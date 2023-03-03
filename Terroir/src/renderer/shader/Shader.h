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

#ifndef TERROIR_SHADER_H
#define TERROIR_SHADER_H

#include "Terroir/src/core/Types.h"
#include "Terroir/src/math/Math.h"

namespace Terroir
{
// Later will open files
class Shader
{
  public:
    // const char* used for compatibility with C-style libraries
    virtual ~Shader() = default;
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    // Uniforms
    virtual void SetUniform(const std::string_view &, i32) const = 0;
    virtual void SetUniform(const std::string_view &, f32) const = 0;
    virtual void SetUniform(const std::string_view &, const Vec2 &) const = 0;
    virtual void SetUniform(const std::string_view &, const Vec3 &) const = 0;
    virtual void SetUniform(const std::string_view &, const Vec4 &) const = 0;
    virtual void SetUniform(const std::string_view &, const Mat3 &) const = 0;
    virtual void SetUniform(const std::string_view &, const Mat4 &) const = 0;

    [[nodiscard]] virtual constexpr const std::string &GetName() const = 0;

    static std::shared_ptr<Shader> Create();
    // Pass a list of shader paths
    static std::shared_ptr<Shader> Create(const std::string_view &,
                                          const std::initializer_list<std::filesystem::path> &);

  private:
    virtual void CheckCompileErrors(u32, const std::string_view &) = 0;
};
} // namespace Terroir

#endif
