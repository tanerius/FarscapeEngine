#include "fspch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>

#pragma warning(disable:4201)
#include <glm/gtc/type_ptr.hpp>
#pragma warning(default:4201)

namespace Farscape {

    static GLenum ShaderTypeFromString(const std::string& type)
    {
        if (type == "vertex")
            return GL_VERTEX_SHADER;
        if (type == "fragment")
            return GL_FRAGMENT_SHADER;

        FS_CORE_ASSERT(false, "Unknown shader type!");
        return 0;
    }


    OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
    {

        std::unordered_map<GLenum, std::string> sources;
        sources[GL_VERTEX_SHADER] = vertexSrc;
        sources[GL_FRAGMENT_SHADER] = fragmentSrc;
        Compile(sources);
    }

    OpenGLShader::OpenGLShader(const std::string& shaderfile)
    {
        std::string source = ReadFile(shaderfile);
        auto shaderSources = PreProcess(source);
        Compile(shaderSources);
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

    std::string OpenGLShader::ReadFile(const std::string& filepath)
    {
        std::string result;
        std::ifstream in(filepath, std::ios::in | std::ios::binary);
        if (in)
        {
            // TODO REFACTOR THIS - make a custom filesyystem --- one day
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
            in.close();
        }
        else
        {
            FS_CORE_ERROR("Could not open shader file '{0}'", filepath);
        }

        return result;
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
    {
        std::unordered_map<GLenum, std::string> shaderSources;

        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find(typeToken, 0);
        while (pos != std::string::npos)
        {
            size_t eol = source.find_first_of("\r\n", pos);
            FS_CORE_ASSERT(eol != std::string::npos, "Syntax error");
            size_t begin = pos + typeTokenLength + 1;
            std::string type = source.substr(begin, eol - begin);
            FS_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

            size_t nextLinePos = source.find_first_not_of("\r\n", eol);
            pos = source.find(typeToken, nextLinePos);
            shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
        }

        return shaderSources;
    }

    void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
    {
        GLuint program = glCreateProgram();
        // TODO: support more than 2 shader source types
        FS_CORE_ASSERT(shaderSources.size() <= 2, "Only 2 shared sources maximum supported atm");
        std::array<GLenum, 2> glShaderIDs;
        int shaderIndex = 0;
        
        for (auto& kv : shaderSources)
        {
            GLenum type = kv.first;
            const std::string& source = kv.second;

            GLuint shader = glCreateShader(type);

            const GLchar* sourceCStr = source.c_str();
            glShaderSource(shader, 1, &sourceCStr, 0);

            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                glDeleteShader(shader);

                FS_CORE_ERROR("{0}", infoLog.data());
                FS_CORE_ASSERT(false, "Shader compilation failure!");
                break;
            }

            glAttachShader(program, shader);
            glShaderIDs[shaderIndex++] = shader;
        }

        m_RendererID = program;

        // Link our program
        glLinkProgram(program);

        // glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(program);

            for (auto id : glShaderIDs)
                glDeleteShader(id);

            FS_CORE_ERROR("{0}", infoLog.data());
            FS_CORE_ASSERT(false, "Shader link failure!");
            return;
        }

        for (auto id : glShaderIDs)
            glDetachShader(program, id);
    }


}
