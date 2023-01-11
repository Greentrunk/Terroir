//
// Created by cjp on 1/9/23.
//

#ifndef TERROIR_DEARIMGUILAYER_H
#define TERROIR_DEARIMGUILAYER_H

#include "Terroir/src/core/event/Event.h"
#include "Terroir/src/core/layer/Layer.h"
#include <Terroir/terroir_export.h>

namespace Terroir
{

class TERROIR_EXPORT DearImGuiLayer : public Layer
{
  public:
    DearImGuiLayer();

    ~DearImGuiLayer() override;

    void OnAttach() override;

    void OnDetach() override;

    void OnEvent(Event &event) override;

    void OnDearImGuiRender() override;

    void Begin();

    void End();

  private:
};

} // namespace Terroir

#endif // TERROIR_DEARIMGUILAYER_H
