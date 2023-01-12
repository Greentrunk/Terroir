#ifndef TERROIR_GRAPHICSCONTEXT_H
#define TERROIR_GRAPHICSCONTEXT_H
namespace Terroir
{
class GraphicsContext
{
  public:
    virtual ~GraphicsContext() = default;

    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;
};
} // namespace Terroir
#endif
