//
//  cgentity.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 4/16/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#include "cgentity.hpp"
#include "cgtexture.hpp"

#include "cghelper.hpp"

#ifdef WINDOWS
#include<windows.h>
#include <GL/glew.h>
#endif



CGCore::Entity::Entity()
{
    Translate = new glm::vec3(0.0f, 0.0f, 0.0f);
    Rotation = new glm::vec4(1.0f,0.0f,0.0f,0.0f);
    Scale = new glm::vec3(1.0f,1.0f,1.0f);
}


CGCore::Entity::Entity(const glm::vec3& T, const glm::vec4& R, const glm::vec3& S)
{
    Translate = new glm::vec3(T.x, T.y, T.z);
    Rotation = new glm::vec4(R.x, R.y, R.z, R.w);
    Scale = new glm::vec3(S.x, S.y, S.z);
}


CGCore::Entity::~Entity()
{
    if(TextureObj != nullptr)
    {
        delete TextureObj;
    }
    delete Translate;
    delete Rotation;
    delete Scale;
}


void CGCore::Entity::ChangeRotation(const glm::vec4& R)
{
    Rotation->x = R.x;
    Rotation->y = R.y;
    Rotation->z = R.z;
    Rotation->w = Rotation->w + R.w;
}


void CGCore::Entity::ChangeTranslation(const glm::vec3& T)
{
    *Translate = *Translate + T;
}

glm::mat4 CGCore::Entity::CreateTransformationMatrix()
{
    return CGCore::CreateTransformationMatrix(GetTranslation(), GetRotationAxis(), GetRotationDeg(), GetScale());
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


void CGCore::Entity::SetTransform(const glm::vec3& T, const glm::vec4& R, const glm::vec3& S)
{
    *Translate = T;
    *Rotation = R;
    *Scale = R;
}


void CGCore::Entity::SetTranslation(const glm::vec3& T)
{
    *Translate =  glm::vec3(T.x, T.y, T.z);
}


void CGCore::Entity::SetRotation(const glm::vec4& R)
{
    *Rotation =  glm::vec4(R.x, R.y, R.z, R.w);
}


void CGCore::Entity::SetScale(const glm::vec3& S)
{
    *Scale =  glm::vec3(S.x, S.y, S.z);
}


void CGCore::Entity::SetVertices(GLuint VAO, GLuint VBO, GLuint BuffSize)
{
    V_VaoAttrIndex = VAO;
    VerticesVBO = VBO;
    VerticesSize = BuffSize;
}

