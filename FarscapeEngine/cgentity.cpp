//
//  cgentity.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 4/16/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#include "cgentity.hpp"
#include "cgtexture.hpp"


CGCore::Entity::~Entity()
{
    if(TextureObj != nullptr)
    {
        delete TextureObj;
    }
}


void CGCore::Entity::DisableEntity() const
{
    glDisableVertexAttribArray(V_VaoAttrIndex);
    glDisableVertexAttribArray(T_VaoAttrIndex);
}


void CGCore::Entity::EnableEntity() const
{
    glEnableVertexAttribArray(V_VaoAttrIndex);
    glEnableVertexAttribArray(T_VaoAttrIndex);
}


void CGCore::Entity::GetVertices(GLfloat* VertexBuffer, GLuint& Size) const
{
    Size = VerticesSize;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VerticesVBO);
    glGetBufferSubData(	GL_ARRAY_BUFFER,
                       0,
                       VerticesSize,
                       VertexBuffer);
    
}


void CGCore::Entity::SetIndices(GLuint VBO, GLuint BuffSize)
{
    IndexBufferVBO = VBO;
    IndicesSize = BuffSize;
}


void CGCore::Entity::SetTexture(GLuint VAO, GLuint VBO, GLuint BuffSize, const char* FilePath)
{
    T_VaoAttrIndex = VAO;
    TextureVBO = VBO;
    TextureUVMapSize = BuffSize;
    if(FilePath != nullptr)
    {
        TextureObj = new CGCore::Texture(FilePath);
    }
    else{
        TextureObj = nullptr;
    }
}


void CGCore::Entity::SetVertices(GLuint VAO, GLuint VBO, GLuint BuffSize)
{
    V_VaoAttrIndex = VAO;
    VerticesVBO = VBO;
    VerticesSize = BuffSize;
}

