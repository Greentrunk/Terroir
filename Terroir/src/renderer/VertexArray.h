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

#ifndef TERROIR_VERTEXARRAY_H
#define TERROIR_VERTEXARRAY_H

#include "buffer/IndexBuffer.h"
#include "buffer/VertexBuffer.h"
#include <memory>
namespace Terroir
{

class VertexArray
{
  public:
    virtual ~VertexArray() = default;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &) = 0;
    virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &) = 0;

    [[nodiscard]] virtual const std::vector<std::shared_ptr<VertexBuffer>> &GetVertexBuffers() const = 0;
    [[nodiscard]] virtual const std::shared_ptr<IndexBuffer> &GetIndexBuffer() const = 0;

    static std::shared_ptr<VertexArray> Create();
};
} // namespace Terroir
#endif
