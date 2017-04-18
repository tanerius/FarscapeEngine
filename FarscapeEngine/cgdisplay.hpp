#ifndef CG_DISPLAY_HPP
#define CG_DISPLAY_HPP

#include <cstdio>
#ifdef WINDOWS
#include<windows.h>
#endif

class GLFWwindow;

namespace CGCore
{

    class DisplayManager
    {
        private:
            const int DisplayWidth = 1280;
            const int DisplayHeight = 720;
            // const int MaxFps = 120;

            GLFWwindow* GLFWWindowPtr = 0; // will hold our window pointer
            double previous_seconds = 0.0f;
            int frame_count = 0;
        
        

        public:
            bool CloseRequested();
            void CreateDisplay();
            void DestroyDisplay();
            void GetInfo();
            float GetRunningTime() const;
            void WriteDisplay(const char* Msg);
            void UpdateDisplay();
            void UpdateFpsCounter();
    };

}

#endif
