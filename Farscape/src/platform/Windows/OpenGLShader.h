#pragma once
#include <string>
#include "Renderer/Shader.h"
#include <glm/glm.hpp>

// TODO: Have to remove
typedef unsigned int GLenum;
typedef int GLint;

namespace Farscape {

    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        OpenGLShader(const std::string& shaderfile);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        void UploadUniformInt(const std::string& name, const int value);

        void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

        void UploadUniformFloat(const std::string& name, const float value);
        void UploadUniformFloat2(const std::string& name, const glm::vec2& vector);
        void UploadUniformFloat3(const std::string& name, const glm::vec3& vector);
        void UploadUniformFloat4(const std::string& name, const glm::vec4& vector);

        virtual const std::string& GetName() const override { return m_Name; }
    private:
        OpenGLShader() = delete;
        std::string ReadFile(const std::string& filepath);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
        void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

        GLint GetUniformLocation(const std::string& name) const;
    private:
        uint32_t m_RendererID;
        std::string m_Name;
        mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;
    };

}