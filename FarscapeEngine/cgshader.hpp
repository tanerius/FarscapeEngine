#ifndef CG_SHADER_HPP
#define CG_SHADER_HPP

#include <vector>
#include <GL/glew.h>
#define MAX_SHADER_LENGTH 262144
namespace CGCore
{
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
            virtual GLuint LoadShaders(const char* VertexShader, const char* FramentShader);
            void StartProgram();
            void StopProgram();

            

    };
}
    

#endif
