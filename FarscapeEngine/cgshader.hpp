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
        float getReflectivity() const { return m_Reflectivity; }
        float getShine() const { return m_ShineDamper; }
        void SetCamPosition(glm::vec3& Pos);
        void SetLightColor(glm::vec3& Color);
        void SetLightDirection(glm::vec3& NewLD);
        void SetReflectivity(float NewReflectivity);
        void SetShineDamper(float NewShine);
        void UnBind();
        void Update(const Transform& transform, const glm::mat4& VP);

        virtual ~Shader();
    protected:
        void ReadUniformVariables();
    private:
        // vertex + fragment shaders
        static const unsigned int NUM_SHADERS = 2;
        static const unsigned int NUM_UNIFORMS = 7;


        void operator=(const Shader& shader) {}
        Shader(const Shader& shader) {}

        std::string LoadShader(const std::string& fileName);
        void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
        GLuint CreateShader(const std::string& text, unsigned int type);

        GLuint m_program;
        GLuint m_shaders[NUM_SHADERS];
        GLuint m_uniforms[NUM_UNIFORMS];
        // TODO: also make these programmatic
        float m_ShineDamper = 1.0f;
        float m_Reflectivity = 0.0f;
        glm::vec3 m_LightDirection;
        glm::vec3 m_LightColor;
        glm::vec3 m_camPosition = glm::vec3(0.0f, 0.0f, -15.0f);
    };

}


#endif
