#ifndef FIGHTERLIKE_H
#define FIGHTERLIKE_H

#include "Terroir.h"

using namespace Terroir;

class FighterLike : public Layer
{
  public:
    explicit FighterLike(const std::string_view &);
    ~FighterLike() override = default;
    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(Timestep) override;
    void OnDearImGuiRender() override;
    void OnEvent(Event &) override;
    void CreateCamera(u32, u32);

  private:
    std::unique_ptr<OrthographicCamera> m_Camera;
    std::shared_ptr<Texture2D> m_SpriteSheet;
};

#endif // FIGHTERLIKE_H