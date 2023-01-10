//
// Created by cjp on 1/8/23.
//

#ifndef TERROIR_LAYER_H
#define TERROIR_LAYER_H

#include <Terroir/terroir_export.h>

#include <utility>
#include "Terroir/pch/Tpch.h"
#include "../event/Event.h"

namespace Terroir
{

	class TERROIR_EXPORT Layer
	{
	public:
		explicit Layer(std::string name) : m_DebugName(std::move(name))
		{
		}

		virtual ~Layer()
		{
			TERR_APP_DEBUG("DELETING LAYER");
		}

		virtual void OnAttach()
		{
		}

		virtual void OnDetach()
		{
		}

		virtual void OnUpdate()
		{
		}

		virtual void OnEvent(Event& event)
		{
		}

		inline const std::string& GetName() const
		{
			return m_DebugName;
		}

	protected:
		std::string m_DebugName;
	};

} // Terroir

#endif //TERROIR_LAYER_H
