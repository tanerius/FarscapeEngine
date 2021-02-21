#pragma once

#include "Core/Window.h"
struct GLFWwindow;


namespace Farscape {

    class GfxContext;

    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProperties& p);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return m_Data.Width;  }
        inline unsigned int GetHeight() const override { return m_Data.Height; }

        inline void SetEventCallbacks(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        inline virtual void* GetRawWindowPointer() const override { return m_Window; }

    private:
        virtual void Init(const WindowProperties& props);
        virtual void Shutdown();

    private:
        GLFWwindow* m_Window;
        GfxContext* m_Context;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;
            bool IsFullScreen;
            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };
}

