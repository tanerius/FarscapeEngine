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


CGCore::Entity::Entity(const char* objModelPath, const char* texturePath, CGCore::Transform* defTransform)
{
    m_Mesh = new CGCore::Mesh(objModelPath);
    if (texturePath != nullptr)
        m_Texture = new CGCore::Texture(texturePath);
    
    if (defTransform == nullptr)
    {
        // default transformation
        m_Transform = new CGCore::Transform(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f,1.0f,1.0f));
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

