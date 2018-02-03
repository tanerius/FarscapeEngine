//
//  Object.h
//  FarscapeEngine
//
//  Created by Taner Selim on 1/25/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef Object_h
#define Object_h

#include <string>

namespace Farscape
{
    // A class out of which all fasrscape objects MUST inherit
    class ObjectBase
    {
        // A method that enables us to output an object in human readable format
        virtual std::string ToString() = 0;
    };
}

#endif /* Object_h */
