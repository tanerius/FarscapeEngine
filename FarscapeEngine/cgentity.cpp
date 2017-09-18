//
//  cgentity.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 4/16/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#include "cgentity.hpp"
#include "cgtexture.hpp"
#include "cgtransform.hpp"
#include "cgmesh.hpp"
#include "cghelper.hpp"

#ifdef WINDOWS
#include<windows.h>
#include <GL/glew.h>
#endif



CGCore::Entity::Entity()
{
    // random triangle
}


CGCore::Entity::Entity(const char* objModelPath, const char* texturePath, CGCore::Transform* t)
{
    m_Mesh = new CGCore::Mesh(objModelPath);
    if (texturePath != nullptr)
        m_Texture = new CGCore::Texture(texturePath);
    
    if (t == nullptr)
    {
        // default transformation
        m_Transform = new CGCore::Transform(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f,1.0f,1.0f));
    }
    else
    {
        m_Transform = new CGCore::Transform(*(t->GetPos()), *(t->GetRot()), *(t->GetScale()));
    }
}


CGCore::Entity::Entity(const char* objModelPath, Texture* texture, CGCore::Transform* t)
{
    m_Mesh = new CGCore::Mesh(objModelPath);
    m_Texture = texture;
    
    if (t == nullptr)
    {
        // default transformation
        m_Transform = new CGCore::Transform(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f,1.0f,1.0f));
    }
    else
    {
        m_Transform = new CGCore::Transform(*(t->GetPos()), *(t->GetRot()), *(t->GetScale()));
    }
}


CGCore::Entity::Entity(const IndexedModel* Model, Texture* texture, Transform* t)
{
    m_Mesh = new CGCore::Mesh(Model);
    m_Texture = texture;
    
    if (t == nullptr)
    {
        // default transformation
        m_Transform = new CGCore::Transform(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f,1.0f,1.0f));
    }
    else
    {
        m_Transform = new CGCore::Transform(*(t->GetPos()), *(t->GetRot()), *(t->GetScale()));
    }
}



CGCore::Entity::~Entity()
{
    delete m_Mesh;
    delete m_Texture;
    delete m_Transform;
}


std::string CGCore::Entity::ToString() const
{
    std::string x = "Entity {}";
    return x;
}

