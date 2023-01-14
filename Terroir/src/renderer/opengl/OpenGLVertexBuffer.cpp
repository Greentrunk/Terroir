#include "OpenGLVertexBuffer.h"
#include "Tpch.h"
#include "glad/glad.h"

namespace Terroir
{
OpenGLVertexBuffer::OpenGLVertexBuffer(f32 *vertices, u32 size)
{
    glGenBuffers(1, &m_RendererId);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &m_RendererId);
}

void OpenGLVertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
}

void OpenGLVertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::SetLayout(const BufferLayout &layout)
{
    m_Layout = layout;
}

} // namespace Terroir
