//
//  Shader.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/27/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef Shader_h
#define Shader_h

#include <string>
#include <GL/glew.h>

#include "../Math/Definitions.h"
#include "../Util/NoCopy.h"

namespace Farscape
{

    class Shader : NoCopy
    {
    public:
        Shader(const std::string& vertexFile, const std::string& fragmentFile);
        ~Shader();
        
        void UseProgram() const;
        
        void LoadInt(GLuint location,   int value);
        void LoadFloat(GLuint location, int value);
        
        // load data to GPU
        void LoadVector2(GLuint location, const glm::vec2& vect);
        void LoadVector3(GLuint location, const glm::vec3& vect);
        void LoadVector4(GLuint location, const glm::vec4& vect);
        
        void LoadMatrix4(GLuint location, const glm::mat4& matrix);
        
    protected:
        // This needs to be overriden from the specific shader child class
        virtual void GetUniforms() = 0;
        GLuint m_id;
    private:
        GLuint LoadShaders( const std::string& vertexShader,
                           const std::string& fragmentShader);
    };
}
#endif /* Shader_h */
