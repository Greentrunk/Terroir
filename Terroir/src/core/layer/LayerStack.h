//
// Created by cjp on 1/8/23.
//

#ifndef TERROIR_LAYERSTACK_H
#define TERROIR_LAYERSTACK_H

#include "Layer.h"
#include "Terroir/pch/Tpch.h"

namespace Terroir
{
// This stack controls engine's layer functionality
class LayerStack
{
  public:
    // Takes pointer to layer for polymorphism
    using LayerPtr = std::unique_ptr<Layer>;
    using LayerStackVec = std::vector<LayerPtr>;
    using LayerStackVecIterator = LayerStackVec::iterator;

    LayerStack();

    ~LayerStack();

    void PushLayer(LayerPtr);

    void PushOverlay(LayerPtr);

    // to be possibly changed
    void PopLayer(LayerPtr &);

    // to be possibly changed
    void PopOverlay(LayerPtr &);

    constexpr LayerStackVecIterator begin()
    {
        return m_Layers.begin();
    }

    constexpr LayerStackVecIterator end()
    {
        return m_Layers.end();
    }

  private:
    LayerStackVec m_Layers;
    u32 m_LayerInsertIndex{0};
};

} // namespace Terroir

#endif // TERROIR_LAYERSTACK_H
