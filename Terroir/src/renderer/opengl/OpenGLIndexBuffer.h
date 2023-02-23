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

#ifndef TERROIR_OPENGLINDEXBUFFER_H
#define TERROIR_OPENGLINDEXBUFFER_H

#include "Terroir/src/renderer/buffer/IndexBuffer.h"

namespace Terroir
{

class OpenGLIndexBuffer : public IndexBuffer
{
  public:
    OpenGLIndexBuffer(u32 *, u32);
    ~OpenGLIndexBuffer() override;

    void Bind() const override;
    void Unbind() const override;

    [[nodiscard]] u32 GetIndexCount() const override
    {
        return m_Count;
    }

  private:
    u32 m_RendererId{};
    u32 m_Count;
};
} // namespace Terroir

#endif // !TERROIR_OPENGLVERTEXBUFFER_H
