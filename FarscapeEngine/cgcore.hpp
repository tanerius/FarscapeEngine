//
//  cgcore.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 4/22/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#ifndef cgcore_h
#define cgcore_h
#include <string>
#ifdef WINDOWS
#include<windows.h>
#endif
namespace CGCore
{
    class Object
    {
    public:
        virtual std::string ToString() const = 0;
    };
    
    
}

#endif /* cgcore_h */
