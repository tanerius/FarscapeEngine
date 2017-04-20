#ifndef CG_DISPLAY_HPP
#define CG_DISPLAY_HPP

#include <cstdio>
#ifdef WINDOWS
#include<windows.h>
#endif
#include "cgcallback.hpp"



namespace CGCore
{

    class DisplayManager : protected CGCallbacks
    {
        private:
            const int DisplayWidth = 1280;
            const int DisplayHeight = 720;
            // const int MaxFps = 120;

            double previous_seconds = 0.0f;
            int frame_count = 0;

        public:
            bool CloseRequested();
            void CreateDisplay();
            void DestroyDisplay();
            void GetInfo();
            void GetResolution(int& W, int& H) const
            {
                W = DisplayWidth;
                H = DisplayHeight;
            }
            float GetRunningTime() const;
            void WriteDisplay(const char* Msg);
            void UpdateDisplay();
            void UpdateFpsCounter();
    };

}

#endif
