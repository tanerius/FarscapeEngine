#pragma once

#include "Farscape/Engine/Layer.h"
namespace Farscape {


	class FARSCAPE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event&) override;
	private:
		float m_Time = 0.0f;
	};

}