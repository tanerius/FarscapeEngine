#pragma once
#include "Core/Core.h"

namespace Farscape {

    class Texture : public ITexture
    {
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void Bind() = 0;
    };

    class Texture2D : public Texture
    {
    public:
        static Ref<Texture2D> Create(const std::string& path);
    };

}
