#include "fspch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>

#pragma warning(disable:4201)
#include <glm/gtc/type_ptr.hpp>
#pragma warning(default:4201)

namespace Farscape {

    OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
        : m_RendererID(0)
    {

        // Create an empty vertex shader handle
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        // Send the vertex shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        const char* source = vertexSrc.c_str();
        glShaderSource(vertexShader, 1, &source, 0);

        // Compile the vertex shader
        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(vertexShader);

            FS_CORE_ERROR("{0}", infoLog.data());
            FS_CORE_ASSERT(false, "Vertex shader compilation failure!");
            return;
        }

        // Create an empty fragment shader handle
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        // Send the fragment shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        source = fragmentSrc.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);

        // Compile the fragment shader
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(fragmentShader);
            // Either of them. Don't leak shaders.
            glDeleteShader(vertexShader);

            FS_CORE_ERROR("{0}", infoLog.data());
            FS_CORE_ASSERT(false, "Fragment shader compilation failure!");
            return;
        }

        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Get a program object.
        m_RendererID = glCreateProgram();

        // Attach our shaders to our program
        glAttachShader(m_RendererID, vertexShader);
        glAttachShader(m_RendererID, fragmentShader);

        // Link our program
        glLinkProgram(m_RendererID);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(m_RendererID);
            // Don't leak shaders either.
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            FS_CORE_ERROR("{0}", infoLog.data());
            FS_CORE_ASSERT(false, "Shader link failure!");
            return;
        }

        // Always detach shaders after a successful link.
        glDetachShader(m_RendererID, vertexShader);
        glDetachShader(m_RendererID, fragmentShader);
    }

    OpenGLShader::OpenGLShader(const std::string& shaderfile)
    {
        std::string result;
        std::ifstream in(shaderfile, std::ios::in, std::ios::binary);
        if (in)
        {
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
            in.close();
        }
        else
        {
            FS_CORE_ASSERT("Could not load shader {0}", shaderfile);
        }
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_RendererID);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::UploadUniformInt(const std::string& name, const int value)
    {
        GLint result = glGetUniformLocation(m_RendererID, name.c_str());
        FS_CORE_ASSERT(result >= 0, "UniformLocation not found");
        glUniform1i(result, value);
    }

    void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
    {
        GLint result = glGetUniformLocation(m_RendererID, name.c_str());
        FS_CORE_ASSERT(result >= 0, "UniformLocation not found");
        glUniformMatrix3fv(result, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
    {
        GLint result = glGetUniformLocation(m_RendererID, name.c_str());
        FS_CORE_ASSERT(result >= 0, "UniformLocation not found");
        glUniformMatrix4fv(result, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::UploadUniformFloat(const std::string& name, const float value)
    {
        GLint result = glGetUniformLocation(m_RendererID, name.c_str());
        FS_CORE_ASSERT(result >= 0, "UniformLocation not found");
        glUniform1f(result, value);
    }

    void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& vector)
    {
        GLint result = glGetUniformLocation(m_RendererID, name.c_str());
        FS_CORE_ASSERT(result >= 0, "UniformLocation not found");
        glUniform2f(result, vector.x, vector.y);
    }

    void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& vector)
    {
        GLint result = glGetUniformLocation(m_RendererID, name.c_str());
        FS_CORE_ASSERT(result >= 0, "UniformLocation not found");
        glUniform3f(result, vector.x, vector.y, vector.z);
    }

    void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& vector)
    {
        GLint result = glGetUniformLocation(m_RendererID, name.c_str());
        FS_CORE_ASSERT(result >= 0, "UniformLocation not found");
        glUniform4f(result, vector.x, vector.y, vector.z, vector.w);
    }

    void OpenGLShader::Compile()
    {

    }

}
