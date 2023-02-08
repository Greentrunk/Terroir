#ifndef TERROIR_RENDERER_H
#define TERROIR_RENDERER_H

#include "RenderCommand.h"
#include "Terroir/src/math/Math.h"
#include "Terroir/src/renderer/OrthographicCamera.h"
#include "Terroir/src/renderer/RendererAPI.h"
#include "Terroir/src/renderer/shader/Shader.h"
#include <memory>
namespace Terroir
{

class Renderer
{
  public:
    static void Init();
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
