//
//  cgcamera.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 4/16/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#ifndef cgcamera_hpp
#define cgcamera_hpp

#include "cgcore.hpp"


#ifdef WINDOWS
#include<windows.h>
#endif

#ifdef USE_GLM
    #include <glm/glm.hpp>
    #include <glm/gtx/transform.hpp>
#endif


namespace CGCore
{
    
    class Camera : public Object
    {
    private:
        // A reference to the display - needed for the callbacks
        glm::mat4 projection;
        glm::vec3 pos;
        glm::vec3 forward;
        glm::vec3 up;
    public:
        Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
        {
            this->pos = pos;
            this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
            this->up = glm::vec3(0.0f, 1.0f, 0.0f);
            this->projection = glm::perspective(fov, aspect, zNear, zFar);
        }
        
        inline glm::mat4 GetViewProjection() const
        {
            return projection * glm::lookAt(pos, pos + forward, up);
        }

        void Move();
        virtual std::string ToString() const override;
    };
}

#endif