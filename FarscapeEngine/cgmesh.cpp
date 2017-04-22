//
//  cgmesh.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 4/22/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#include "cgmesh.hpp"
#include <string>


#include <GL/glew.h>
#include <glm/glm.hpp>


std::string CGCore::Vertex::ToString() const
{
    std::string x = "V(" + std::to_string(Pos->x) +
        ", " + std::to_string(Pos->y) +
        ", " + std::to_string(Pos->z) + ")\n" +
        "UV(" + std::to_string(TexCoord->x) +
        ", " + std::to_string(TexCoord->y) + ")\n" +
        "N(" + std::to_string(Normal->x) +
        ", " + std::to_string(Normal->y) +
        ", " + std::to_string(Normal->z) + ")\n";
    
    return x;
}


CGCore::Vertex::~Vertex()
{
    delete this->Pos;
    delete this->TexCoord;
    delete this->Normal;
}


void CGCore::IndexedModel::CalcNormals()
{
    for(unsigned int i = 0; i < indices.size(); i += 3)
    {
        int i0 = indices[i];
        int i1 = indices[i + 1];
        int i2 = indices[i + 2];
        
        glm::vec3 v1 = positions[i1] - positions[i0];
        glm::vec3 v2 = positions[i2] - positions[i0];
        
        glm::vec3 normal = glm::normalize(glm::cross(v1, v2));
        
        normals[i0] += normal;
        normals[i1] += normal;
        normals[i2] += normal;
    }
    
    for(unsigned int i = 0; i < positions.size(); i++)
        normals[i] = glm::normalize(normals[i]);
}


