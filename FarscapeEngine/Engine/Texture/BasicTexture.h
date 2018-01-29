//
//  BasicTexture.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/28/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef BasicTexture_h
#define BasicTexture_h

#include <GL/glew.h>
#include <string>

#include "../Util/NoCopy.h"

namespace Farscape {

    
    class BasicTexture : public NoCopy
    {
    public:
        BasicTexture() = default;
        BasicTexture(const std::string& file);
        
        ~BasicTexture();
        
        void LoadFromFile (const std::string& file);
        
        void BindTexture() const;
        
        
    private:
        GLuint m_id;
    };
}

#endif /* BasicTexture_h */
