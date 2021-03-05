#include "fspch.h"
#include "Renderer/RenderCommand.h"

#include "Windows/OpenGLRendererAPI.h"

namespace Farscape {

    Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope<OpenGLRendererAPI>();

}
