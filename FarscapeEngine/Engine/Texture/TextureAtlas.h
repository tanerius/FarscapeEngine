#ifndef TEXTUREATLAS_H_INCLUDED
#define TEXTUREATLAS_H_INCLUDED

#include "BasicTexture.h"
#include "../Math/Definitions.h"
#include <vector>

namespace Farscape
{
    class TextureAtlas : public BasicTexture
    {
        public:
            TextureAtlas(const std::string& textureFileName);

            std::vector<GLfloat> GetTexture(const Vector2di& coords);

        private:
            int m_imageSize;
            int m_individualTextureSize;
    };
}
#endif // TEXTUREATLAS_H_INCLUDED
