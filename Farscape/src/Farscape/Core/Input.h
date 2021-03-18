#pragma once
#include "Codes.h"

namespace Farscape
{
    // Input will definitely be a singleton
    class Input : public IInput
    {
    public:
        static bool IsKeyPressed(KeyCode keycode);

        static bool IsMouseButtonPressed(int button);
        static float GetMouseX();
        static float GetMouseY();
        static std::pair<float, float> GetMousePosition();
    };
}