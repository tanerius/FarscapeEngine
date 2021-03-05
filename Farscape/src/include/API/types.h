#pragma once
#include <cstdint>

namespace Farscape {

	enum class PrimitiveType
	{
		None = 0, Triangles, Lines
	};

	using RendererID = uint32_t;

}