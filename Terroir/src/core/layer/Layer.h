//
// Created by cjp on 1/8/23.
//

#ifndef TERROIR_LAYER_H
#define TERROIR_LAYER_H

#include "Terroir/pch/Tpch.h"
#include "Terroir/src/core/Timestep.h"
#include "Terroir/src/core/event/Event.h"

namespace Terroir
{

class Layer
{
  public:
    explicit Layer(std::string_view name) : m_DebugName(std::move(name))
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

    virtual void OnUpdate(Timestep)
    {
    }

    virtual void OnEvent(Event &event)
    {
    }

    virtual void OnDearImGuiRender()
    {
    }

    [[nodiscard]] constexpr const std::string &GetName() const
    {
        return m_DebugName;
    }

  protected:
    std::string m_DebugName; // NOLINT
};

} // namespace Terroir

#endif // TERROIR_LAYER_H
