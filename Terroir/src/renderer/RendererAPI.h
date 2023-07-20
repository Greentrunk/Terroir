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

#ifndef TERROIR_RENDERERAPI_H
#define TERROIR_RENDERERAPI_H

#include "Terroir/src/math/Math.h"
#include "VertexArray.h"
#include <memory>

namespace Terroir
{

class RendererAPI
{
  public:
    virtual ~RendererAPI() = default;

    enum class API
    {
        None = 0,
        OpenGL = 1,
        Direct = 2,
        Vulkan = 3,
        Metal = 4,
    };

    virtual void Init() = 0;
    virtual void SetViewport(u32, u32, u32, u32) = 0;
    virtual void Clear(const Vec4 &) = 0;
    virtual void DrawIndexed(const std::shared_ptr<VertexArray> &, u32 indexCount = 0) = 0;
    virtual void DrawArrays(u32) = 0;

    static API GetAPI()
    {
        return s_API;
    }

  private:
    static API s_API;
};

} // namespace Terroir

#endif // !TERROIR_RENDERERAPI_H
