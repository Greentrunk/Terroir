#ifndef TERROIR_RENDERCOMMAND_H
#define TERROIR_RENDERCOMMAND_H

#include "RendererAPI.h"

namespace Terroir
{

class RenderCommand
{
  public:
    inline static void Init()
    {
      s_RendererAPI->Init();
    }

    static void Clear()
    {
        s_RendererAPI->Clear();
    }

    static void Clear(const glm::vec4 &color)
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
