#pragma once
#include "Core/Core.h"
#include "Core/Buffer.h"
#include "Renderer/RendererAPI.h"

namespace Farscape {

    enum class TextureFormat
    {
        None = 0,
        RGB = 1,
        RGBA = 2,
        Float16 = 3
    };

    enum class TextureWrap
    {
        None = 0,
        Clamp = 1,
        Repeat = 2
    };

    class Texture : public ITexture, public RefCounter
    {
    public:
        virtual ~Texture() {}

        virtual void Bind(uint32_t slot = 0) const = 0;

        virtual TextureFormat GetFormat() const = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual uint32_t GetMipLevelCount() const = 0;

        virtual RendererID GetRendererID() const = 0;

        static uint32_t GetBPP(TextureFormat format);
        static uint32_t CalculateMipMapCount(uint32_t width, uint32_t height);

        virtual bool operator==(const Texture& other) const = 0;
    };

    class Texture2D : public Texture
    {
    public:
        static SharedRef<Texture2D> Create(TextureFormat format, uint32_t width, uint32_t height, TextureWrap wrap = TextureWrap::Clamp);
        static SharedRef<Texture2D> Create(const std::string& path, bool srgb = false);

        virtual void Lock() = 0;
        virtual void Unlock() = 0;

        virtual void Resize(uint32_t width, uint32_t height) = 0;
        virtual Buffer GetWriteableBuffer() = 0;

        virtual bool Loaded() const = 0;

        virtual const std::string& GetPath() const = 0;
    };

    class TextureCube : public Texture
    {
    public:
        static SharedRef<TextureCube> Create(TextureFormat format, uint32_t width, uint32_t height);
        static SharedRef<TextureCube> Create(const std::string& path);

        virtual const std::string& GetPath() const = 0;
    };

}
