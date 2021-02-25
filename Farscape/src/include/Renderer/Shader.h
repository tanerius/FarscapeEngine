#pragma once
#include "Core/Core.h"
#include <string>

namespace Farscape {

    class Shader : public IShader
    {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        static Shader* Create(const std::string& path);
        static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
    };

}
