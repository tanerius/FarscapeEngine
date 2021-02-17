#pragma once
#include "Renderer/GfxContext.h"

struct GLFWwindow;

namespace Farscape {

	class OpenGLContext : public GfxContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle = nullptr;
	};

}
