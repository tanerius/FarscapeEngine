//
//  NoCopy.h
//  FarscapeEngine
//
//  Created by Taner Selim on 1/25/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef NoCopy_h
#define NoCopy_h

namespace Farscape
{
    // An inherritable struct that does not allow kids to make copies
    struct NoCopy
    {
        NoCopy() = default;
        NoCopy(const NoCopy&) = delete;
        NoCopy& operator=(const NoCopy&) = delete;
    };
}


#endif /* NoCopy_h */
