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

#ifndef TERROIR_OPENGLRENDERERAPI_H
#define TERROIR_OPENGLRENDERERAPI_H

#include "Terroir/src/renderer/RendererAPI.h"
#

namespace Terroir
{

class OpenGLRendererAPI : public RendererAPI
{
  public:
    ~OpenGLRendererAPI() override = default;

    // OpenGL default setups
    void Init() override;

    // Set viewport
    void SetViewport(u32, u32, u32, u32) override;

    // Clear screen
    void Clear(const Vec4 &) override;

    void DrawIndexed(const std::shared_ptr<VertexArray> &) override;
    void DrawArrays(u32) override;
};

} // namespace Terroir

#endif // !TERROIR_OPENGLRENDERERAPI_H
