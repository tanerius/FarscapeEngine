//
//  cgtransform.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 4/23/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#ifndef cgtransform_h
#define cgtransform_h


#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>


namespace CGCore
{

    // Representation for the transformations
    struct Transform
    {
    public:
        Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
        {
            this->pos = pos;
            this->rot = rot;
            this->scale = scale;
        }


        // Generate transformation matrix
        inline glm::mat4 GetTransformationMatrix() const
        {
            glm::mat4 posMat = glm::translate(pos); // Translation matrix
            glm::mat4 scaleMat = glm::scale(scale);
            glm::mat4 rotX = glm::rotate(rot.x, glm::vec3(1.0, 0.0, 0.0));
            glm::mat4 rotY = glm::rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));
            glm::mat4 rotZ = glm::rotate(rot.z, glm::vec3(0.0, 0.0, 1.0));
            glm::mat4 rotMat = rotX * rotY * rotZ;
            return posMat * rotMat * scaleMat;
        }


        inline glm::mat4 GetMVP(const glm::mat4& VP) const
        {
            glm::mat4 M = GetTransformationMatrix();

            return VP * M;
            // for camera.GetViewProjection() * GetModel(); do return glm::mat4&
        }

        inline glm::vec3* GetPos() { return &pos; }
        inline glm::vec3* GetRot() { return &rot; }
        inline glm::vec3* GetScale() { return &scale; }

        inline void SetPos(glm::vec3& pos) { this->pos = pos; }
        inline void SetRot(glm::vec3& rot) { this->rot = rot; }
        inline void SetScale(glm::vec3& scale) { this->scale = scale; }
    protected:
    private:
        glm::vec3 pos;
        glm::vec3 rot;
        glm::vec3 scale;
    };
}


#endif /* cgtransform_h */
