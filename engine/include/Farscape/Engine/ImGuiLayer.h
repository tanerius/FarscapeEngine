#pragma once

#include "Farscape/Engine/Layer.h"
#include "Farscape/Events/MouseEvent.h"
#include "Farscape/Events/keyevent.h"
#include "Farscape/Events/ApplicationEvent.h"

namespace Farscape {


	class FARSCAPE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}