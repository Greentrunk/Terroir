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

#include "OpenGLRendererAPI.h"
#include "Terroir/src/math/Math.h"
#include "Tpch.h"
#include <glad/glad.h>

namespace Terroir
{
void OpenGLRendererAPI::Init()
{
    // Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Culling
    glEnable(GL_CULL_FACE);

    // Depth
    glEnable(GL_DEPTH_TEST);
}

void OpenGLRendererAPI::SetViewport(u32 x, u32 y, u32 width, u32 height)
{
    glViewport(static_cast<i32>(x), static_cast<i32>(y), static_cast<i32>(width), static_cast<i32>(height));
}

void OpenGLRendererAPI::Clear(const Vec4 &color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray, u32 indexCount)
{
    auto count{ indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetIndexCount() };
    glDrawElements(GL_TRIANGLES, static_cast<i32>(count), GL_UNSIGNED_INT,
       nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLRendererAPI::DrawArrays(u32 count)
{
    glDrawArrays(GL_TRIANGLES, 0, static_cast<i32>(count));
}

} // namespace Terroir
