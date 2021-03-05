#pragma once

#include "Core.h"

namespace Farscape
{
    // Input will definitely be a singleton
    class Input : public IInput
    {
    public:
        static bool IsKeyPressed(int keycode);

        static bool IsMouseButtonPressed(int button);
        static float GetMouseX();
        static float GetMouseY();
        static std::pair<float, float> GetMousePosition();
    };
}