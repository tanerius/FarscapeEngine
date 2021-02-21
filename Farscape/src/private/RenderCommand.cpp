#include "fspch.h"
#include "Renderer/RenderCommand.h"

#include "Windows/OpenGLRendererAPI.h"

namespace Farscape {

    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}
