#pragma once

#include <glm/glm.hpp>
#include "Vinyl/Core/Input/KeyCodes.h"
#include "Vinyl/Core/Input/MouseCodes.h"

namespace Vinyl
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}