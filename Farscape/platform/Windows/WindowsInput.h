#pragma once
#include "Core/Input.h"

namespace Farscape {
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual double GetMousePosXImpl() override;
		virtual double GetMousePosYImpl() override;
		virtual std::pair<double, double> GetMousePosImpl() override;
	};
}