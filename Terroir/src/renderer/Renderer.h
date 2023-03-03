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

#ifndef TERROIR_RENDERER_H
#define TERROIR_RENDERER_H

#include "RenderCommand.h"
#include "Terroir/src/math/Math.h"
#include "Terroir/src/renderer/RendererAPI.h"
#include "Terroir/src/renderer/camera/OrthographicCamera.h"
#include "Terroir/src/renderer/shader/Shader.h"
#include <memory>
namespace Terroir
{

class Renderer
{
  public:
    static void Init();
    static void Shutdown();

    static void OnWindowResize(u32, u32);

    static void BeginScene(OrthographicCamera &);
    static void EndScene();

    static void Submit(const std::shared_ptr<VertexArray> &, const std::shared_ptr<Shader> &,
                       const Mat4 &transform = Mat4(1.0f));

    static RendererAPI::API GetAPI()
    {
        return RendererAPI::GetAPI();
    }


  private:
    using SceneData = struct SceneData
    {
        Mat4 m_ViewProjectionMatrix;
    };

    static std::unique_ptr<SceneData> m_SceneData;
};

};     // namespace Terroir
#endif // !TERROIR_RENDERER_H
