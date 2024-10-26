#pragma once

#include <glm/glm.hpp>
#include "Vinyl/Core/Input/KeyCodes.h"
#include "Vinyl/Core/Input/MouseCodes.h"

namespace Vinyl
{
	class Input
	{
	public:
		static bool IsKeyDown(KeyCode keycode);

		static bool IsMouseDown(MouseCode mousecode);

		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}