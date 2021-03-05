#pragma once
#include "Core.h"
#include "LayerStack.h"
#include "Renderer/Camera.h"
#include "Timestep.h"

namespace Farscape {
    class WindowCloseEvent;
    class WindowResizeEvent;
    class Window;
    class Event;
    class ImGuiLayer;
    class Shader;
    class VertexBuffer;
    class IndexBuffer;
    class VertexArray;

    struct ApplicationProps
    {
        std::string Name;
        uint32_t WindowWidth, WindowHeight;
    };


    class Application : public IApplication
    {
    public:
        Application(const ApplicationProps& props = { "Farscape Engine", 1280, 720 });
        virtual ~Application();

        void Execute();

        virtual void OnInit() {}
        virtual void OnShutdown() {}
        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void RenderImGui();

        std::string OpenFile(const std::string& filter) const;

        static inline Application& Get()
        {
            return *s_Instance;
        }

        inline Window& GetWindowReference() { return *m_Window; }

    private:
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);
    private:
        // a platform agnostic window - consider a unique pointer
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer = nullptr;
        bool m_IsRunning = true;
        LayerStack m_layerStack;
        float m_LastTick = 0.0f;
        bool m_IsMinimized = false;
        
        
    private:
        static Application* s_Instance;
    };

    // Should be defined in a client
    Application* CreateApplication();
}