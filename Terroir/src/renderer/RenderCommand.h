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

#ifndef TERROIR_RENDERCOMMAND_H
#define TERROIR_RENDERCOMMAND_H

#include "RendererAPI.h"

namespace Terroir
{

class RenderCommand
{
  public:
    static void Init()
    {
        s_RendererAPI->Init();
    }

    static void SetViewport(u32 x, u32 y, u32 width, u32 height)
    {
        s_RendererAPI->SetViewport(x, y, width, height);
    }

    static void Clear(const Vec4 &color = Vec4(0.0f, 0.0f, 0.0f, 1.0f))
    {
        s_RendererAPI->Clear(color);
    }

    static void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray)
    {
        s_RendererAPI->DrawIndexed(vertexArray);
    }

  private:
    static std::unique_ptr<RendererAPI> s_RendererAPI;
};
} // namespace Terroir

#endif // !TERROIR_RENDERCOMMAND_H
