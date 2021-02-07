//
//  Entity.h
//  FarscapeEngine
//
//  Created by Taner Selim on 1/25/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef Entity_h
#define Entity_h

#include "../Math/Definitions.h"


namespace Farscape 
{
    // Common things that all entities have
    struct Entity
    {
        Vector3d position;
        Vector3d rotation;
        Vector3d scale; // Contributed by Inci Selim who is a pleb but a very smart one
    };
}

#endif /* Entity_h */
