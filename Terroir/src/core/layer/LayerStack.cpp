//
// Created by cjp on 1/8/23.
//

#include "LayerStack.h"
#include "Tpch.h"

namespace Terroir
{
// Set insert iterator pointer to the beginning on construction
LayerStack::LayerStack() = default;

// Cleanup
LayerStack::~LayerStack()
{
    TERR_ENGINE_INFO("DELETING LAYERSTACK");
    for (auto &layer : m_Layers)
    {
        layer.reset(nullptr);
    }
}

void LayerStack::PushLayer(LayerStack::LayerPtr layer)
{
    m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, std::move(layer));
    ++m_LayerInsertIndex;
}

void LayerStack::PushOverlay(LayerStack::LayerPtr overlay)
{

    m_Layers.emplace_back(std::move(overlay));
}

void LayerStack::PopLayer(LayerStack::LayerPtr &layer)
{
    if (auto it = std::ranges::find(m_Layers, layer); it != m_Layers.end())
    {
        m_Layers.erase(it);
        --m_LayerInsertIndex;
    }
}

void LayerStack::PopOverlay(LayerStack::LayerPtr &overlay)
{
    if (auto it = std::ranges::find(m_Layers, overlay); it != m_Layers.end())
    {
        m_Layers.erase(it);
    }
}
} // namespace Terroir
