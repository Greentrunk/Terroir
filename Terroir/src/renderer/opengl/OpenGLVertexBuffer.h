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

#ifndef TERROIR_OPENGLVERTEXBUFFER_H
#define TERROIR_OPENGLVERTEXBUFFER_H

#include "Terroir/src/renderer/buffer/VertexBuffer.h"
namespace Terroir
{

class OpenGLVertexBuffer : public VertexBuffer
{
  public:
    OpenGLVertexBuffer(f32 *, u32);
    ~OpenGLVertexBuffer() override;

    void Bind() const override;
    void Unbind() const override;

    void SetLayout(const BufferLayout &) override;
    [[nodiscard]] constexpr const BufferLayout &GetLayout() const override
    {
        return m_Layout;
    }

  private:
    u32 m_RendererId{};
    BufferLayout m_Layout{};
};
} // namespace Terroir

#endif // !TERROIR_OPENGLVERTEXBUFFER_H
