#pragma once

#include "Core.h"

namespace Farscape
{
    // Input will definitely be a singleton
    class Input : public IInput
    {
    protected:
        Input() = default;
    public:
        Input(const Input&) = delete;
        Input& operator=(const Input&) = delete;

        inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
        inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
        // these would look much better in a struct
        inline static std::pair<double, double> GetMousePos() { return s_Instance->GetMousePosImpl(); }
        inline static double GetMousePosX() { return s_Instance->GetMousePosXImpl(); }
        inline static double GetMousePosY() { return s_Instance->GetMousePosYImpl(); }
    protected:
        virtual bool IsKeyPressedImpl(int keycode) = 0; // platform implement
        virtual bool IsMouseButtonPressedImpl(int button) = 0;
        virtual std::pair<double, double> GetMousePosImpl() = 0;
        virtual double GetMousePosXImpl() = 0;
        virtual double GetMousePosYImpl() = 0;
        

    private:
        static Input* s_Instance;
    };
}