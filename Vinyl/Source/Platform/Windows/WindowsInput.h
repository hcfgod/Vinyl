#pragma once

#include "Vinyl/Input.h"
#include "Vinyl/Core/KeyCodes.h"
#include "Vinyl/Core/MouseCodes.h"

namespace Vinyl
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(KeyCode key) override;

		virtual bool IsMouseButtonPressedImpl(MouseCode button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}