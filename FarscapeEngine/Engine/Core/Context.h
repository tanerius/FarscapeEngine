//
//  Context.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/25/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef Context_h
#define Context_h

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Farscape
{
    struct Context
    {
        Context() = default;
        
        GLFWwindow* GLFWWindowPtr = 0;
        int ScreenWidth = 0;
        int ScreenHeight = 0;
        float AspectRatio = 0.0f;
        bool FullScreen = false;
        bool hasContext = false;
    };
    
    class ContextWrapper
    {
        public:
            ContextWrapper(const std::string& AppName, const int& w, const int& h);
            ~ContextWrapper();
            Context GetContext() {return m_context;}
        
            void SetShowInfo(const bool b) {m_showInfo = b;}
            void ShowStartupInfo();
            void ToggleFullscreen();
            void Update();
            void Shutdown();
        
        private:
            std::string m_windowTitle;
            Context m_context;
            void ShowContextInfo();
            double delta_time = 0.0f;
            double previous_seconds = 0.0f;
            int frame_count = 0;
            bool m_showInfo = false;
            bool m_UpdateTitle = false;
            bool m_isFullscreen = false;
        
        
    };
}

#endif /* Context_h */
