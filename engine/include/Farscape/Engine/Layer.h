#pragma once

#include "Farscape/Engine/Core.h"
#include "Farscape/Events/Event.h"

namespace Farscape {

	
	class FARSCAPE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event&) {}

		inline const std::string& GetName() const { return m_LayerName; }
	protected:
		std::string m_LayerName;
	};

}
