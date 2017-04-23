//
//  cgcamera.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 4/20/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#include "cgcamera.hpp"

#ifdef WINDOWS
    #include<windows.h>
#endif

#ifdef USE_GLM
    #include <glm/glm.hpp>
#endif

#include <string>

std::string CGCore::Camera::ToString() const 
{
    std::string x = "Camera {\n";
    
    x = x + "ProjectionMatrix \n{\n";
    
    for(int j = 0; j < 4; j++)
    {
        for(int i = 0; i < 4; i++)
        {
            x += std::to_string(projection[i][j]) + "\t";
        }
        x += "\n";
    }
    x += "}\nPos(";
    x += std::to_string(pos.x) + ", " + std::to_string(pos.y) + ", " + std::to_string(pos.z) +")\n";
    x += "Fwd(";
    x += std::to_string(forward.x) + ", " + std::to_string(forward.y) + ", " + std::to_string(forward.z) +")\n";
    x += "Up(";
    x += std::to_string(up.x) + ", " + std::to_string(up.y) + ", " + std::to_string(up.z) +")\n";
    x += "}\n";
    
    /*
     
     glm::mat4 projection;
     glm::vec3 pos;
     glm::vec3 forward;
     glm::vec3 up;
     
     */
    return x;
}



void CGCore::Camera::Move()
{
    return;
}
