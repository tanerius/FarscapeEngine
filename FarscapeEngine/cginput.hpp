//
//  cginput.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 4/27/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#ifndef cginput_hpp
#define cginput_hpp

#include "cgcore.hpp"


#ifdef WINDOWS
#include<windows.h>
#endif

namespace CGCore
{
    class DisplayManager;
    class Camera;

    class Input : public Object
    {
        private:
            bool m_isAttached = false;
            DisplayManager* m_display = nullptr;
            Camera* m_camera = nullptr;

        public:
            Input(DisplayManager* currentDisplay, Camera* currentCam);
            virtual ~Input() {}
            void Move();
            virtual std::string ToString() const override;
    };
}

#endif