#pragma once

#include "Core.h"

namespace Farscape {

	class Event;

	class FARSCAPE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event&) {}

		inline const std::string& GetName() const { return m_LayerName; }
	protected:
		std::string m_LayerName;
	};

}
