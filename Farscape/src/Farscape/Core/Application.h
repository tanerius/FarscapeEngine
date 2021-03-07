#pragma once
#include "Core/Core.h"
#include "Core/Timestep.h"
#include "Core/Window.h"
#include "Core/LayerStack.h"

#include "Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"

namespace Farscape {
    struct ApplicationProps
    {
        std::string Name;
        uint32_t WindowWidth, WindowHeight;
    };

    class Application
    {
    public:
        Application(const ApplicationProps& props = { "Farscape Engine", 1280, 720 });
        virtual ~Application();

        void Run();

        virtual void OnInit() {}
        virtual void OnShutdown() {}
        virtual void OnUpdate(Timestep) {}

        virtual void OnEvent(Event& event);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
        void RenderImGui();

        std::string OpenFile(const std::string& filter) const;

        inline Window& GetWindow() { return *m_Window; }

        inline float GetFPS() const { return m_fps; }

        static inline Application& Get() { return *s_Instance; }

        float GetTime() const; // TODO: This should be in "Platform"
    private:
        bool OnWindowResize(WindowResizeEvent& e);
        bool OnWindowClose(WindowCloseEvent& e);
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true, m_Minimized = false;
        LayerStack m_LayerStack;
        ImGuiLayer* m_ImGuiLayer;
        Timestep m_TimeStep;
        float m_fps = 60.0f;

        float m_LastFrameTime = 0.0f;

        static Application* s_Instance;
    };

    // Implemented by CLIENT
    Application* CreateApplication();
}