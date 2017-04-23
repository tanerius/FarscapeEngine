#ifndef CG_SHADER_HPP
#define CG_SHADER_HPP

#include <string>
#include <GL/glew.h>
#include "cgtransform.hpp"

namespace CGCore
{
    
    class Shader
    {
    public:
        Shader(const std::string& fileName);
        
        void Bind();
        void Update(const Transform& transform, const glm::mat4& VP);
        
        virtual ~Shader();
    protected:
    private:
        static const unsigned int NUM_SHADERS = 2; // vertex + fragment shaders
        static const unsigned int NUM_UNIFORMS = 3; 
        
        void operator=(const Shader& shader) {}
        Shader(const Shader& shader) {}
        
        std::string LoadShader(const std::string& fileName);
        void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
        GLuint CreateShader(const std::string& text, unsigned int type);
        
        GLuint m_program;
        GLuint m_shaders[NUM_SHADERS];
        GLuint m_uniforms[NUM_UNIFORMS];
    };
    
}
    

#endif
