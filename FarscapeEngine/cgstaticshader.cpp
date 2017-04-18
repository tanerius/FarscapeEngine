#include "cgshader.hpp"
#include "cgstaticshader.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

CGCore::StaticShader::StaticShader() : Shader()
{
    LoadShaders(VERTEX_FILENAME, FRAGMENT_FILENAME);
}

void CGCore::StaticShader::BindAttributes()
{
    BindAttribute(0, "position");
    BindAttribute(1, "textureCoords"); // sine vao1 ia now used it has to be enabled in the renderer
}


void CGCore::StaticShader::GetAllUniformLocations()
{
    Loc_transformationMatrix = GetUniformLocation("transformationMatrix");
    Loc_TextureSamplerHnd = GetUniformLocation("textureSampler");
    Loc_ProjectionMatrix = GetUniformLocation("projectionMatrix");
}

void CGCore::StaticShader::LoadTextureToSampler(const GLuint TextureID, const int SamplerUnit)
{
    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0 + SamplerUnit);
    glBindTexture(GL_TEXTURE_2D, TextureID);
    
    LoadUniform(Loc_TextureSamplerHnd, 0);
}


#ifdef USE_GLM
void CGCore::StaticShader::LoadTransformationMatrix(glm::mat4& M)
{
    LoadUniform(Loc_transformationMatrix, M);
}
void CGCore::StaticShader::LoadProjectionMatrix(glm::mat4& M)
{
    LoadUniform(Loc_ProjectionMatrix, M);
}
#else
void CGCore::StaticShader::LoadTransformationMatrix(Mat4f& M)
{
    LoadUniform(Loc_transformationMatrix, M);
}
#endif
