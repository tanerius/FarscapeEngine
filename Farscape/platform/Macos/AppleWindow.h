#pragma once

#include "Farscape/Engine/Window.h"
#include <GLFW/glfw3.h>

namespace Farscape {

    class AppleWindow : public Window
    {
    public:
        AppleWindow(const WindowProperties& p);
        virtual ~AppleWindow();

        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return m_Data.Width;  }
        inline unsigned int GetHeight() const override { return m_Data.Height; }

        inline void SetEventCallbacks(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

    private:
        virtual void Init(const WindowProperties& props);
        virtual void Shutdown();

    private:
        GLFWwindow* m_Window;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;
            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };
}

