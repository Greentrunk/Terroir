#include "OpenGLTexture.h"
#ifndef __OPENGLTEXTURE_H__
#define __OPENGLTEXTURE_H__

namespace Terroir
{

OpenGLTexture2D::OpenGLTexture2D(const std::filesystem::path &path) : m_Path(path)
{
}
OpenGLTexture2D::~OpenGLTexture2D()
{
}

void OpenGLTexture2D::Bind()
{
}
} // namespace Terroir
#endif // __OPENGLTEXTURE_H__