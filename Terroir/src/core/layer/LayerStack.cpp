//
// Created by cjp on 1/8/23.
//

#include "LayerStack.h"
#include "Tpch.h"

namespace Terroir
{
	// Set insert iterator pointer to the beginning on construction
	LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layers.begin();
	}

	// Cleanup
	LayerStack::~LayerStack()
	{
		TERR_ENGINE_INFO("DELETING LAYERSTACK");
		for (auto& layer: m_Layers)
		{
			layer.reset(nullptr);
		}
	}

	void LayerStack::PushLayer(LayerStack::LayerPtr layer)
	{
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, std::move(layer));

	}

	void LayerStack::PushOverlay(LayerStack::LayerPtr overlay)
	{

		m_Layers.emplace_back(std::move(overlay));
	}

	void LayerStack::PopLayer(LayerStack::LayerPtr& layer)
	{
		if (auto it = std::find(m_Layers.begin(), m_Layers.end(), layer); it != m_Layers.end())
		{
			m_Layers.erase(it);
			--m_LayerInsert;
		}
	}

	void LayerStack::PopOverlay(LayerStack::LayerPtr& overlay)
	{
		if (auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay); it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}
} // Terroir