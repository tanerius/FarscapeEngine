#pragma once

#include "fspch.h"
#include "Core.h"


namespace Farscape {
    class Event;

    struct WindowProperties
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProperties(
            const std::string& title = "Farscape Engine",
            unsigned int width = 1280,
            unsigned int height = 720
        )
            : Title(title)
            , Width(width)
            , Height(height) {}
    };

    // A window for desktops
    class Window : public IWindow
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;
        virtual ~Window() {}
        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual std::pair<uint32_t, uint32_t> GetSize() const = 0;
        virtual std::pair<float, float> GetWindowPos() const = 0;

        virtual void SetEventCallbacks(const EventCallbackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void* GetRawWindowPointer() const = 0;

        // Creation function with reasonable defaults from the struct
        // This should be implemented for every platform !!
        static Window* Create(const WindowProperties& p = WindowProperties());
    };

}