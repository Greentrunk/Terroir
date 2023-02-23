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

        GLenum INTERNAL_FORMAT{0}, DATA_FORMAT{0};

        if (channels == 4)
        {
            INTERNAL_FORMAT = GL_RGBA8;
            DATA_FORMAT = GL_RGBA;
        }
        else if (channels == 3)
        {
            INTERNAL_FORMAT = GL_RGB8;
            DATA_FORMAT = GL_RGB;
        }

        TERR_ENGINE_ASSERT(INTERNAL_FORMAT & DATA_FORMAT, "OpenGL format not supported!");

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, INTERNAL_FORMAT, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, DATA_FORMAT, GL_UNSIGNED_BYTE, data);

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