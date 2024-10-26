#include "vlpch.h"

#include "Vinyl/Core/Input/Input.h"
#include "Vinyl/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Vinyl
{
	bool Input::IsKeyDown(const KeyCode keycode)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS;
	}

	bool Input::IsMouseDown(const MouseCode mousecode)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, mousecode);

		return state == GLFW_PRESS;
	}

	glm::vec2  Input::GetMousePosition()
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}

	float Input::GetMouseY()
	{
		return GetMousePosition().y;
	}
}