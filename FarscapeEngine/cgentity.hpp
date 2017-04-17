//
//  cgentity.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 4/16/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#ifndef cgentity_hpp
#define cgentity_hpp
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
        
        public:
        Entity() {}
        ~Entity();
        
        void DisableEntity() const;
        void EnableEntity() const;
        GLuint GetIndexBufferVBO() const { return IndexBufferVBO; }
        GLuint GetIBSize() const { return IndicesSize; }
        void GetVertices(GLfloat* VertexBuffer, GLuint& Size) const;
        Texture* GetTextureObj() const { return TextureObj; }
        
        void SetIndices(GLuint VBO, GLuint BuffSize);
        void SetTexture(GLuint VAO, GLuint VBO, GLuint BuffSize, const char* FilePath);
        void SetVertices(GLuint VAO, GLuint VBO, GLuint BuffSize);
        
    };
}
#endif /* cgentity_hpp */
