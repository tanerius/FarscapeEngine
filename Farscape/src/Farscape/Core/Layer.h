#pragma once

#include "Core/Core.h"
#include "Core/Timestep.h"

namespace Farscape {

    class Event;


    class Layer : public ILayer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event&) {}

        inline const std::string& GetName() const { return m_LayerName; }
    protected:
        std::string m_LayerName;
    };

}
