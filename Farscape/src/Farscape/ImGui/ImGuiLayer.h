#pragma once
#include "fspch.h"
#include "Core/Layer.h"

namespace Farscape {


    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ImGuiLayer(const std::string& name);
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();
    private:
    #if defined(WIN32)
        float m_Time = 0.0f;
    #endif
    };

}