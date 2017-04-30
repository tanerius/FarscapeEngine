#include "cgshader.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include <cstdio>



CGCore::Shader::Shader(const std::string& fileName)
{
    m_program = glCreateProgram();

    m_shaders[0] = CreateShader(LoadShader(fileName + ".vsh"), GL_VERTEX_SHADER);
    m_shaders[1] = CreateShader(LoadShader(fileName + ".fsh"), GL_FRAGMENT_SHADER);
    // Attach shaders to program
    for(unsigned int i = 0; i < NUM_SHADERS; i++)
        glAttachShader(m_program, m_shaders[i]);
    // Bind the location attrs from shader
    glBindAttribLocation(m_program, 0, "position");
    glBindAttribLocation(m_program, 1, "texCoord");
    glBindAttribLocation(m_program, 2, "normal");
    // Link Program
    glLinkProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");

    m_uniforms[0] = glGetUniformLocation(m_program, "MVP");
    m_uniforms[1] = glGetUniformLocation(m_program, "Normal");
    m_uniforms[2] = glGetUniformLocation(m_program, "lightDirection");

    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, true, "ERROR: Invalid shader program");

}

CGCore::Shader::~Shader()
{
    for(unsigned int i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }

    glDeleteProgram(m_program);
}

void CGCore::Shader::Bind()
{
    glUseProgram(m_program);
}

void CGCore::Shader::UnBind()
{
    glUseProgram(0);
}

void CGCore::Shader::Update(const Transform& transform, const glm::mat4& VP)
{
    glm::mat4 MVP = transform.GetMVP(VP);
    glm::mat4 Normal = transform.GetModel();

    glUniformMatrix4fv(m_uniforms[0], 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(m_uniforms[1], 1, GL_FALSE, &Normal[0][0]);
    glUniform3f(m_uniforms[2], 0.0f, 0.0f, 1.0f);
}

std::string CGCore::Shader::LoadShader(const std::string& fileName)
{
    std::string output;
    std::ifstream file;
    file.open((fileName).c_str());

    std::string line;

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
            output.append(line + "\n");
        }
    }
    else
    {
        std::cerr << "ERROR: Unable to load shader: " << fileName << std::endl;
        exit(EXIT_FAILURE);
    }

    return output;
}

void CGCore::Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);


    std::cout << "Checking shaders..." << std::endl;

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
        exit(EXIT_FAILURE);
    }
}

GLuint CGCore::Shader::CreateShader(const std::string& text, unsigned int type)
{
    GLuint shader = glCreateShader(type);

    if(shader == 0){
        std::cerr << "ERROR: Error compiling shader type " << type << std::endl;
        exit(EXIT_FAILURE);
    }

    const GLchar* p[1];
    p[0] = text.c_str();
    GLint lengths[1];
    lengths[0] = text.length();

    glShaderSource(shader, 1, p, lengths);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "ERROR: Error compiling shader!");

    return shader;
}


