//
//  Definitions.h
//  FarscapeEngine
//
//  Created by Taner Selim on 1/25/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef Definitions_h
#define Definitions_h

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <algorithm> // for std::max

namespace Farscape
{

    using Vector2d = glm::vec2;
    using Vector3d = glm::vec3;
    using Matrix4 = glm::mat4;
    
    static float PI_CONST = 3.141592653589f;
    
    template <class T>
    T Clamp(const T& n, const T& lower, const T& upper) {
        return std::max(lower, std::min(n, upper));
    }
}
#endif /* Definitions_h */
