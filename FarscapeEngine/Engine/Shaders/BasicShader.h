//
//  MeshShader.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/28/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef BasicShader_h
#define BasicShader_h

#include "Shader.h"

namespace Farscape {
    class BasicShader : public Shader
    {
        public:
            BasicShader(const std::string& vertexFile   = "BasicVertex",
                        const std::string& fragmentFile = "BasicFragment");
        
            void LoadProjectionViewMatrix   (const glm::mat4& pvMatrix);
            void LoadModelMatrix            (const glm::mat4& matrix);
        
        private:
            virtual void GetUniforms() override;
        
            GLuint m_locationProjectionViewMatrix;
            GLuint m_locationModelMatrix;
    };
}

#endif /* BasicShader_h */
