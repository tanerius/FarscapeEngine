#pragma once 

namespace Farscape {

	enum class RendererAPI {
		None = 0,
		OpenGL = 1,
		DirectX = 2,
		Metal = 3,
		Vulcan = 4
	};

	class Renderer
	{
	public:
		static inline RendererAPI GetAPI() { return Renderer::s_RendererAPI;  }
	private:
		static RendererAPI s_RendererAPI;
	};
		
}
