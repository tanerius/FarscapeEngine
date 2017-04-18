//
//  cgentity.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 4/16/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#ifndef cgentity_hpp
#define cgentity_hpp
#ifdef WINDOWS
#include<windows.h>
#endif

#ifdef USE_GLM
    #include <glm/glm.hpp>
#endif

#include <GL/glew.h>

namespace CGCore
{
    class Texture;

    // Container wit a model together with the transform matrix
    class Entity
    {
        private:
        GLuint V_VaoAttrIndex; // Vao attr index for vertex buffer
        GLuint VerticesVBO; // VBO id for model
        GLuint VerticesSize; // BufferSize

        GLuint IndexBufferVBO; // VBO id for model
        GLuint IndicesSize; // BufferSize

        GLuint T_VaoAttrIndex; // Vao attr index for Texture buffer
        GLuint TextureVBO; // VBO id for texture
        GLuint TextureUVMapSize; // Tex map UV BufferSize
        Texture* TextureObj = nullptr; // Texture (if used)
        
        glm::vec3* Translate = nullptr;
        glm::vec4* Rotation = nullptr;
        glm::vec3* Scale = nullptr;
    

        public:
        Entity(const glm::vec3& T, const glm::vec4& R, const glm::vec3& S); // Transformation constructor
        Entity(); // No transformation constructor
        ~Entity();

        void ChangeRotation(const glm::vec4& R);
        void ChangeTranslation(const glm::vec3& T);
        
        glm::mat4 CreateTransformationMatrix();
        
        void DisableEntity() const;
        void EnableEntity() const;
        GLuint GetIndexBufferVBO() const { return IndexBufferVBO; }
        GLuint GetIBSize() const { return IndicesSize; }
        Texture* GetTextureObj() const { return TextureObj; }
        
        glm::vec3 GetTranslation() const { return *Translate; }
        glm::vec3 GetRotationAxis() const
        {
            return glm::vec3(
                Rotation->x,
                Rotation->y,
                Rotation->z
                             );
        }
        float GetRotationDeg() const
        {
            return Rotation->w;
        }
        
        glm::vec3 GetScale() const { return *Scale; }
        
        void GetVertices(GLfloat* VertexBuffer, GLuint& Size) const;

        void SetIndices(GLuint VBO, GLuint BuffSize);
        void SetTexture(GLuint VAO, GLuint VBO, GLuint BuffSize, const char* FilePath);
        
        void SetTransform(const glm::vec3& T, const glm::vec4& R, const glm::vec3& S);
        void SetTranslation(const glm::vec3& T);
        void SetRotation(const glm::vec4& R);
        void SetScale(const glm::vec3& S);
        void SetVertices(GLuint VAO, GLuint VBO, GLuint BuffSize);

    };
}
#endif /* cgentity_hpp */
