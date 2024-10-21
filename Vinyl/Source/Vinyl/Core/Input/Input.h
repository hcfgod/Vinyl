#pragma once

#include "Vinyl/Core/Base.h"

#include "Vinyl/Core/Input/KeyCodes.h"
#include "Vinyl/Core/Input/MouseCodes.h"

namespace Vinyl
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}