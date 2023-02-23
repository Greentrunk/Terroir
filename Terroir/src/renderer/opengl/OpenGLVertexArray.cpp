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

#include "OpenGLVertexArray.h"
#include "core/Assert.h"
#include <glad/glad.h>

namespace Terroir
{

static constexpr GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
    using enum ShaderDataType;
    switch (type)
    {
    case Vec:
        return GL_FLOAT;
    case Vec2:
        return GL_FLOAT;
    case Vec3:
        return GL_FLOAT;
    case Vec4:
        return GL_FLOAT;
    case Mat3:
        return GL_FLOAT;
    case Mat4:
        return GL_FLOAT;
    case I:
        return GL_INT;
    case I2:
        return GL_INT;
    case I3:
        return GL_INT;
    case I4:
        return GL_INT;
    case Bool:
        return GL_BOOL;
    default:
        return 0;
    }
}

OpenGLVertexArray::OpenGLVertexArray()
{
    glGenVertexArrays(1, &m_RendererId);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &m_RendererId);
}

void OpenGLVertexArray::Bind()
{
    glBindVertexArray(m_RendererId);
}

void OpenGLVertexArray::Unbind()
{
    glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer)
{
    TERR_ENGINE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "VB has no layout!");

    glBindVertexArray(m_RendererId);
    vertexBuffer->Bind();
    const auto &layout = vertexBuffer->GetLayout();
    u32 index{0};
    for (const auto &element : layout)
    {
        glVertexAttribPointer(index, static_cast<GLint>(element.GetComponentCount()),
                              ShaderDataTypeToOpenGLBaseType(element.GetShaderDataType()),
                              element.IsNormalized() ? GL_TRUE : GL_FALSE, static_cast<GLint>(layout.GetStride()),
                              reinterpret_cast<const void *>(element.GetOffset()));
        glEnableVertexAttribArray(index);
        ++index;
    }
    m_VertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer)
{
    glBindVertexArray(m_RendererId);
    indexBuffer->Bind();

    m_IndexBuffer = indexBuffer;
}
} // namespace Terroir
