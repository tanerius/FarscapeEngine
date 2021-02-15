#pragma once
#include "Farscape/Engine/Layer.h"

namespace Farscape {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnUpdate();
		void OnEvent(Event&);
		void OnAttach();
		void OnDetach();
	private:
		float m_Time = 0.0f;
	};
}