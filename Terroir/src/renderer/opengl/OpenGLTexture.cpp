#ifndef __OPENGLTEXTURE_H__
#define __OPENGLTEXTURE_H__

#include "OpenGLTexture.h"
#include "Tpch.h"
#include "core/Assert.h"
#include "stb_image.h"
#include <glad/glad.h>

namespace Terroir
{

OpenGLTexture2D::OpenGLTexture2D(const std::filesystem::path &path) : m_Path(path)
{
    i32 width, height, channels;

    // flip the image properly
    stbi_set_flip_vertically_on_load(true);

    // Load data
    if (auto data = stbi_load(path.generic_string().c_str(), &width, &height, &channels, 0); data == nullptr)
    {

        TERR_ENGINE_ASSERT(data, "Failed to load image data!");
    }
    else
    {

        m_Width = width;
        m_Height = height;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, data);

        // minimap?

        // Set wrapping/filtering options

        stbi_image_free(data);
    }
}
OpenGLTexture2D::~OpenGLTexture2D()
{
    glDeleteTextures(1, &m_RendererID);
}

void OpenGLTexture2D::Bind(u32 slot)
{
    glBindTextureUnit(slot, m_RendererID);
}
} // namespace Terroir
#endif // __OPENGLTEXTURE_H__