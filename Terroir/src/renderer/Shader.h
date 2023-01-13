#ifndef TERROIR_SHADER_H
#define TERROIR_SHADER_H

#include "Terroir/src/core/Types.h"
#include <string>

namespace Terroir
{
// Later will open files
class Shader
{
  public:
    Shader(const std::string &, const std::string &);
    ~Shader();
    void Bind() const;
    void Unbind() const;
    // inline void setBool(const std::string &name, bool value) const
    // {
    //     glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
    // }
    // // ------------------------------------------------------------------------
    // inline void setInt(const std::string &name, int value) const
    // {
    //     glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
    // }
    // // ------------------------------------------------------------------------
    // inline void setFloat(const std::string &name, float value) const
    // {
    //     glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
    // }

  private:
    void CheckCompileErrors(u32, const std::string &);
    u32 m_ID;
};
} // namespace Terroir

#endif
