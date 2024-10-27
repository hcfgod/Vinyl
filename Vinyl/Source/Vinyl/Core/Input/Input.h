#pragma once

#include <glm/glm.hpp>
#include "Vinyl/Core/Input/KeyCodes.h"
#include "Vinyl/Core/Input/MouseButtons.h"

namespace Vinyl
{
	class Input
	{
	public:
		static bool IsKeyHeld(KeyCode keycode);

		static bool IsMouseButtonHeld(MouseButton mousebutton);

		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}