#pragma once
#include <cstdint>

namespace Vinyl
{
	using MouseCode = uint16_t;

	namespace Mouse
	{
		enum : MouseCode
		{
			// From glfw3.h
			Button0 = 0,
			Button1 = 1,
			Button2 = 2,
			Button3 = 3,
			Button4 = 4,
			Button5 = 5,
			Button6 = 6,
			Button7 = 7,

			ButtonLast = Button7,
			ButtonLeft = Button0,
			ButtonRight = Button1,
			ButtonMiddle = Button2
		};
	}
}

#define VL_MOUSE_BUTTON_0      ::Vinyl::Mouse::Button0
#define VL_MOUSE_BUTTON_1      ::Vinyl::Mouse::Button1
#define VL_MOUSE_BUTTON_2      ::Vinyl::Mouse::Button2
#define VL_MOUSE_BUTTON_3      ::Vinyl::Mouse::Button3
#define VL_MOUSE_BUTTON_4      ::Vinyl::Mouse::Button4
#define VL_MOUSE_BUTTON_5      ::Vinyl::Mouse::Button5
#define VL_MOUSE_BUTTON_6      ::Vinyl::Mouse::Button6
#define VL_MOUSE_BUTTON_7      ::Vinyl::Mouse::Button7
#define VL_MOUSE_BUTTON_LAST   ::Vinyl::Mouse::ButtonLast
#define VL_MOUSE_BUTTON_LEFT   ::Vinyl::Mouse::ButtonLeft
#define VL_MOUSE_BUTTON_RIGHT  ::Vinyl::Mouse::ButtonRight
#define VL_MOUSE_BUTTON_MIDDLE ::Vinyl::Mouse::ButtonMiddle