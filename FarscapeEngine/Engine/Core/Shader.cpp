//
//  Shader.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/27/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#include "Shader.h"
#include "../Util/File.h"

#include <string>
#include <GL/glew.h>

// Snadalone functions
GLuint CompileShader(const GLchar* source, GLenum shaderType)
{
    auto shaderID = glCreateShader(shaderType);
    
    glShaderSource(shaderID, 1, &source, nullptr);
    glCompileShader(shaderID);
    
    GLint isSuccess = 0;
    GLchar infoLog[512];
    
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isSuccess);
    if(!isSuccess)
    {
        glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
        throw std::runtime_error ("Unable to load a shader: " + std::string(infoLog));
    }
    
    return shaderID;
}

GLuint LinkProgram(GLuint vertexShaderID, GLuint fragmentShaderID)
{
    auto id = glCreateProgram();
    
    glAttachShader(id, vertexShaderID);
    glAttachShader(id, fragmentShaderID);
    
    glLinkProgram(id);
    
    return id;
}



Farscape::Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile)
:   m_id    (LoadShaders(vertexFile, fragmentFile))
{
    UseProgram();
}


void Farscape::Shader::LoadInt(GLuint location, int value)
{
    glUniform1i(location, value);
}

void Farscape::Shader::LoadFloat(GLuint location, int value)
{
    glUniform1f(location, value);
}

void Farscape::Shader::LoadVector2(GLuint location, const glm::vec2& vect)
{
    glUniform2f(location, vect.x, vect.y);
}

void Farscape::Shader::LoadVector3(GLuint location, const glm::vec3& vect)
{
    glUniform3f(location, vect.x, vect.y, vect.z);
}

void Farscape::Shader::LoadVector4(GLuint location, const glm::vec4& vect)
{
    glUniform4f(location, vect.x, vect.y, vect.z, vect.w);
}

void Farscape::Shader::LoadMatrix4(GLuint location, const glm::mat4& matrix)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

Farscape::Shader::~Shader()
{
    glDeleteProgram(m_id);
}

void Farscape::Shader::UseProgram() const
{
    glUseProgram(m_id);
}

GLuint Farscape::Shader::LoadShaders(const std::string& vertexShader,
                   const std::string& fragmentShader)
{
    
    auto vertexSource   = Farscape::File::GetInstance()->GetFileContents("Shaders/" + vertexShader     + ".glsl");
    auto fragmentSource = Farscape::File::GetInstance()->GetFileContents("Shaders/" + fragmentShader   + ".glsl");
    
    auto vertexShaderID     = CompileShader(vertexSource.c_str(),   GL_VERTEX_SHADER);
    auto fragmentShaderID   = CompileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);
    
    auto shaderID = LinkProgram(vertexShaderID, fragmentShaderID);
    
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
    
    return shaderID;
}

