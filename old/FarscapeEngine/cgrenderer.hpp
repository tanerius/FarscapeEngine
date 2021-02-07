#ifndef CG_RENDERER_HPP
#define CG_RENDERER_HPP

#include<glm/glm.hpp>

#include <GL/glew.h>

namespace CGCore
{
    class StaticShader;
    class Entity;
    class DisplayManager;
    

    // Renderer class 
    class Renderer
    {
        private:
            glm::mat4* ProjectionMatrix = nullptr;
            static constexpr float FOV = 70.0f;  //field of view for projection matrix
            static constexpr float NEAR_PLANE = 0.1f;  //field of view for projection matrix
            static constexpr float FAR_PLANE = 1000.0f;  //field of view for projection matrix
            void CreateProjectionMatrix(const DisplayManager* DM);
        
        public:
            Renderer(const DisplayManager* DM);
            ~Renderer();
            glm::mat4 GetProjection() {
                if(ProjectionMatrix!= nullptr)
                {
                    return *ProjectionMatrix;
                }
                else
                {
                    return glm::mat4(1.0f);
                }
            }
            void Prepare();
            void Render(GLenum RenderMode, GLuint StartIndex, GLuint NumberOfVertices);
            // void RenderFromBufferIndex(GLuint BufferIndex,GLenum RenderMode, GLenum DataType, GLuint NumberOfVertices);
            // void RenderFromBufferIndex(Entity* EntityObj, StaticShader* EntityShader);
            void SetStates();
    };

} 

#endif
