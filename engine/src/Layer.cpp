#pragma once
#include "fspch.h"
#include "Farscape/Engine/Layer.h"

namespace Farscape {
	Layer::Layer(const std::string& name)
		: m_LayerName(name) {}

	Layer::~Layer() {}
}