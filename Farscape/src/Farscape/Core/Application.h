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

    class Application : public IApplication
    {
    public:
        Application();
        virtual ~Application();

        void Execute();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        inline static Application& Get()
        {
            return *s_Instance;
        }

        inline Window& GetWindowReference() { return *m_Window; }

    private:
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);
    private:
        // a platform agnostic window - consider a unique pointer
        Window* m_Window = nullptr;
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