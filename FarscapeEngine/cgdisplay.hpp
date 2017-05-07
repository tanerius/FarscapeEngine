#ifndef CG_DISPLAY_HPP
#define CG_DISPLAY_HPP

#include <cstdio>
#ifdef WINDOWS
#include<windows.h>
#endif
#include "cgcallback.hpp"



namespace CGCore
{

    class DisplayManager : public CGCallbacks
    {
        private:
            const int DisplayWidth = 800;
            const int DisplayHeight = 600;
            // const int MaxFps = 120;

            double previous_seconds = 0.0f;
            double delta_time = 0.0f;
            int frame_count = 0;
            bool m_UsingMouse;

        public:
            bool CloseRequested();
            void CreateDisplay(const bool UsesMouse = true);
            void DestroyDisplay();
            double GetDeltaTime() { return delta_time; }
            bool* GetHandledKeys() { return HandledKeys; }
            double GetMouseOffsetY() const { return MouseOffsetY; }
            double GetMouseOffsetX() const { return MouseOffsetX; }
        
            void GetInfo();
            void GetResolution(int& W, int& H) const
            {
                W = DisplayWidth;
                H = DisplayHeight;
            }
            float GetRunningTime() const;
            void SetMouseSensitivity(const float s);
            void ResetOffset();
            void WriteDisplay(const char* Msg);
            void UpdateDisplay();
            void UpdateFpsCounter();
    };

}

#endif
