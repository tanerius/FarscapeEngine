#ifndef CG_SHADER_HPP
#define CG_SHADER_HPP

#include <vector>
#include <GL/glew.h>

#ifdef USE_GLM
// Use C++11 standard
#include<glm/glm.hpp>
// translate, rotate, scale, perspective
#include <glm/gtc/matrix_transform.hpp>
// value_ptr
#include <glm/gtc/type_ptr.hpp>
#endif

#define MAX_SHADER_LENGTH 262144
namespace CGCore
{
    class Vec3;
    class Vec2;
    class Mat4f;
    // An abstract class representing a shader - can't be instantiated on its own
    class Shader
    {
        private:
            GLuint ProgramID;
            bool ReadFile ( const char* file_name, char* shader_str, int max_len);
        protected:
            virtual void BindAttributes(); // MUST BE OVERRIDEN !!!
        public:
            void BindAttribute(int Attrib, const GLchar* VarName);
            void CleanUp();
            GLuint GetProgramID() const { return ProgramID; }
            GLint GetUniformLocation(const char* LocationName);
            virtual void GetAllUniformLocations(); // Also must be overriden
            // Load vars to uniform locations in shader
            // Float laoder
            void LoadUniform(GLint Location, float VarValue) const;
        
#ifdef USE_GLM
            // Vec3 Loader
        void LoadUniform(GLint Location, const glm::vec3& VarValue) const;
            // Mat4 loader
        void LoadUniform(GLint Location, const glm::mat4& Matrix) const;
#else
            // Vec3 Loader
            void LoadUniform(GLint Location, const Vec3& VarValue) const;
            // Mat4 loader
            void LoadUniform(GLint Location, const Mat4f& Matrix) const;
#endif
            // bool loader
            void LoadUniform(GLint Location, const bool VarValue) const;
        
        
            virtual GLuint LoadShaders(const char* VertexShader, const char* FramentShader);
            void StartProgram();
            void StopProgram();
            bool ValidateProgram();

        

    };
}
    

#endif
