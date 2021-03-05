#include "fspch.h"
#include "Renderer/RenderCommand.h"

#include "platform/Windows/OpenGLRendererAPI.h"

namespace Farscape {

    Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope<OpenGLRendererAPI>();

}
