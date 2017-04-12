#ifndef CG_RENDERER_HPP
#define CG_RENDERER_HPP

#include <GL/glew.h>

namespace CGCore
{
    class RawModel;

    // Renderer class 
    class Renderer
    {
        private:

        public:
            void Prepare();
            void Render(GLenum RenderMode, GLuint StartIndex, GLuint NumberOfVertices);
            void RenderFromBufferIndex(GLuint BufferIndex,GLenum RenderMode, GLenum DataType, GLuint NumberOfVertices);
            void SetStates();
    };

} 

#endif
