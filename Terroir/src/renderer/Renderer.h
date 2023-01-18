#ifndef TERROIR_RENDERER_H
#define TERROIR_RENDERER_H

#include "RenderCommand.h"
#include "Terroir/src/renderer/OrthographicCamera.h"
#include "Terroir/src/renderer/RendererAPI.h"
#include "Terroir/src/renderer/Shader.h"
namespace Terroir
{

class Renderer
{
  public:
    static void BeginScene(OrthographicCamera &);
    static void EndScene();

    static void Submit(const std::shared_ptr<VertexArray> &, const std::shared_ptr<Shader> &);

    static RendererAPI::API GetAPI()
    {
        return RendererAPI::GetAPI();
    }

  private:
    using SceneData = struct SceneData
    {
        glm::mat4 m_ViewProjectionMatrix;
    };

    static SceneData *m_SceneData;
};

};     // namespace Terroir
#endif // !TERROIR_RENDERER_H
