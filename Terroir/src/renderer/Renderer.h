#ifndef TERROIR_RENDERER_H
#define TERROIR_RENDERER_H

namespace Terroir
{
enum class RendererAPI
{
    None = 0,
    OpenGL = 1,
    Direct = 2,
    Vulkan = 3,
    Metal = 4,
};

class Renderer
{
  public:
    inline static RendererAPI GetRenderAPI()
    {
        return s_RendererAPI;
    }
    static RendererAPI s_RendererAPI;
};

};     // namespace Terroir
#endif // !TERROIR_RENDERER_H
