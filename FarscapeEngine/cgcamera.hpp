//
//  cgcamera.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 4/16/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#ifndef cgcamera_hpp
#define cgcamera_hpp

#ifdef WINDOWS
#include<windows.h>
#endif

#ifdef USE_GLM
    #include <glm/glm.hpp>
#endif

#include <GL/glew.h>

namespace CGCore
{

    
    class Camera 
    {
    private:
        // A reference to the display - needed for the callbacks
        DisplayManager* Display = nullptr;
        glm::vec3* Position = nullptr;
        float Roll = 0.0f;
        float Pitch = 0.0f;
        float Yaw = 0.0f;
    public:
        Camera(DisplayManager* D);
        ~Camera();

        

        glm::vec3 GetPosition();
        float GetPitch() const { return Pitch; }
        float GetRoll() const { return Pitch; }
        float GetYaw() const { return Pitch; }
        void Move();
    };
}

#endif