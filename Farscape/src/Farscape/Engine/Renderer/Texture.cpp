#include "fspch.h"
#include "Renderer/Texture.h"
#include "Renderer/RendererAPI.h"

#include "Video/OpenGL/OpenGLTexture.h"

namespace Farscape {

    SharedRef<Texture2D> Texture2D::Create(TextureFormat format, unsigned int width, unsigned int height, TextureWrap wrap)
    {
        switch (RendererAPI::Current())
        {
        case RendererAPIType::None: return nullptr;
        case RendererAPIType::OpenGL: return SharedRef<OpenGLTexture2D>::Create(format, width, height, wrap);
        }
        return nullptr;
    }

    SharedRef<Texture2D> Texture2D::Create(const std::string& path, bool srgb)
    {
        switch (RendererAPI::Current())
        {
        case RendererAPIType::None: return nullptr;
        case RendererAPIType::OpenGL: return SharedRef<OpenGLTexture2D>::Create(path, srgb);
        }
        return nullptr;
    }

    SharedRef<TextureCube> TextureCube::Create(TextureFormat format, uint32_t width, uint32_t height)
    {
        switch (RendererAPI::Current())
        {
        case RendererAPIType::None: return nullptr;
        case RendererAPIType::OpenGL: return SharedRef<OpenGLTextureCube>::Create(format, width, height);
        }
        return nullptr;
    }

    SharedRef<TextureCube> TextureCube::Create(const std::string& path)
    {
        switch (RendererAPI::Current())
        {
        case RendererAPIType::None: return nullptr;
        case RendererAPIType::OpenGL: return SharedRef<OpenGLTextureCube>::Create(path);
        }
        return nullptr;
    }

    uint32_t Texture::GetBPP(TextureFormat format)
    {
        switch (format)
        {
        case TextureFormat::RGB:    return 3;
        case TextureFormat::RGBA:   return 4;
        }
        return 0;
    }

    uint32_t Texture::CalculateMipMapCount(uint32_t width, uint32_t height)
    {
        uint32_t levels = 1;
        while ((width | height) >> levels)
            levels++;

        return levels;
    }

}
