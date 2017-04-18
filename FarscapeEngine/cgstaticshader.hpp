#ifndef CG_STATICSHADER_HPP
#define CG_STATICSHADER_HPP

#include <vector>
#include <GL/glew.h>

namespace CGCore
{
    // Forward declares so not to clutter with includes
    class Vec3;
    class Mat4f;
     //static const char* VERTEX_FILENAME = "/Users/tanerselim/Dev/Quadtree_LOD/core/shaders/hello_tex.vsh";
     //static const char* FRAGMENT_FILENAME = "/Users/tanerselim/Dev/Quadtree_LOD/core/shaders/hello_tex.fsh";

#ifdef WINDOWS
    // Shaders with a texture
    static const char* VERTEX_FILENAME = "C:\\Users\\taner\\Documents\\Dev\\FarscapeEngine\\FarscapeEngine\\shaders\\hello_tex.vsh";
    static const char* FRAGMENT_FILENAME = "C:\\Users\\taner\\Documents\\Dev\\FarscapeEngine\\FarscapeEngine\\shaders\\hello_tex.fsh";

#else
    // Shaders with a texture
    static const char* VERTEX_FILENAME = "/Users/tanerselim/Dev/FarscapeEngine/FarscapeEngine/shaders/hello_tex.vsh";
    static const char* FRAGMENT_FILENAME = "/Users/tanerselim/Dev/FarscapeEngine/FarscapeEngine/shaders/hello_tex.fsh";
#endif

    //textureCoords
    class StaticShader : public CGCore::Shader
    {
        private:
            GLint Loc_transformationMatrix;
            GLint Loc_TextureSamplerHnd;
        protected:
            virtual void BindAttributes() override;
        public:
            StaticShader();
            virtual ~StaticShader() {}
            virtual void GetAllUniformLocations() override;

            void LoadTextureToSampler(const GLuint TextureID, const int SamplerUnit) ;
#ifdef USE_GLM
            void LoadTransformationMatrix(glm::mat4& M);

#else
            void LoadTransformationMatrix(Mat4f& M);
#endif
    };
}

#endif
