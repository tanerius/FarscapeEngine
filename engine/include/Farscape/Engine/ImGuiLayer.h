#pragma once

#include "Farscape/Engine/Layer.h"
#include "Farscape/Events/keyevent.h"
#include "Farscape/Events/MouseEvent.h"
#include "Farscape/Events/keyevent.h"
#include "Farscape/Events/ApplicationEvent.h"

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
		/*
		KeyPressed, KeyReleased,
		MouseBtnPressed, MouseBtnReleased, MouseMoved, MouseScrolled,
		*/
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
	private:
		float m_Time = 0.0f;
	};

}