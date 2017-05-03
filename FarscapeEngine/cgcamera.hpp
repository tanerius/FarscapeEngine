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



        const float MOVE_SPEED = 0.025f;
    public:
        Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
        {
            this->pos = pos;
            this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
            this->up = glm::vec3(0.0f, 1.0f, 0.0f);
            this->projection = glm::perspective(fov, aspect, zNear, zFar);
        }

        virtual ~Camera() {}
        
        glm::vec3 GetPosition() const { return pos; }


        void MoveLeft();
        void MoveRight();
        void MoveUp();
        void MoveDown();
        void MoveIn();
        void MoveBack();

        void Roll(int direction);
        void Pitch(int direction);
        void Yaw(int direction);

        inline glm::mat4 GetProjectionMatrix() const
        {
            return projection;
        }

        inline glm::mat4 GetViewMatrix() const
        {
            return glm::lookAt(pos, pos + forward, up);
        }

        inline glm::mat4 GetViewProjection() const
        {
            return projection * glm::lookAt(pos, pos + forward, up);
        }


        void Reposition(glm::vec3& positionDelta);
        virtual std::string ToString() const override;
    };
}

#endif
