#pragma once
#include "fspch.h"
#include "Core/Layer.h"

namespace Farscape {
	Layer::Layer(const std::string& name)
		: m_LayerName(name) {}

	Layer::~Layer() {}
}