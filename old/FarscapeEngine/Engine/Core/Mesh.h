//
//  Mesh.h
//  FarscapeEngine
//
//  Created by Taner Selim on 2/4/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef Mesh_h
#define Mesh_h

#include <GL/glew.h>
#include <vector>


namespace Farscape
{
    struct Mesh
    {
        std::vector<GLfloat> vertexPositions;
        std::vector<GLfloat> textureCoords;
        std::vector<GLuint> indices;
    };
}


#endif /* Mesh_h */
