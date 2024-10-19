#pragma once

namespace Vinyl
{
	using KeyCode = uint16_t;

	namespace Key
	{
		enum : KeyCode
		{
			// From glfw3.h
			Space = 32,
			Apostrophe = 39, /* ' */
			Comma = 44, /* , */
			Minus = 45, /* - */
			Period = 46, /* . */
			Slash = 47, /* / */

			D0 = 48, /* 0 */
			D1 = 49, /* 1 */
			D2 = 50, /* 2 */
			D3 = 51, /* 3 */
			D4 = 52, /* 4 */
			D5 = 53, /* 5 */
			D6 = 54, /* 6 */
			D7 = 55, /* 7 */
			D8 = 56, /* 8 */
			D9 = 57, /* 9 */

			Semicolon = 59, /* ; */
			Equal = 61, /* = */

			A = 65,
			B = 66,
			C = 67,
			D = 68,
			E = 69,
			F = 70,
			G = 71,
			H = 72,
			I = 73,
			J = 74,
			K = 75,
			L = 76,
			M = 77,
			N = 78,
			O = 79,
			P = 80,
			Q = 81,
			R = 82,
			S = 83,
			T = 84,
			U = 85,
			V = 86,
			W = 87,
			X = 88,
			Y = 89,
			Z = 90,

			LeftBracket = 91,  /* [ */
			Backslash = 92,  /* \ */
			RightBracket = 93,  /* ] */
			GraveAccent = 96,  /* ` */

			World1 = 161, /* non-US #1 */
			World2 = 162, /* non-US #2 */

			/* Function keys */
			Escape = 256,
			Enter = 257,
			Tab = 258,
			Backspace = 259,
			Insert = 260,
			Delete = 261,
			Right = 262,
			Left = 263,
			Down = 264,
			Up = 265,
			PageUp = 266,
			PageDown = 267,
			Home = 268,
			End = 269,
			CapsLock = 280,
			ScrollLock = 281,
			NumLock = 282,
			PrintScreen = 283,
			Pause = 284,
			F1 = 290,
			F2 = 291,
			F3 = 292,
			F4 = 293,
			F5 = 294,
			F6 = 295,
			F7 = 296,
			F8 = 297,
			F9 = 298,
			F10 = 299,
			F11 = 300,
			F12 = 301,
			F13 = 302,
			F14 = 303,
			F15 = 304,
			F16 = 305,
			F17 = 306,
			F18 = 307,
			F19 = 308,
			F20 = 309,
			F21 = 310,
			F22 = 311,
			F23 = 312,
			F24 = 313,
			F25 = 314,

			/* Keypad */
			KP0 = 320,
			KP1 = 321,
			KP2 = 322,
			KP3 = 323,
			KP4 = 324,
			KP5 = 325,
			KP6 = 326,
			KP7 = 327,
			KP8 = 328,
			KP9 = 329,
			KPDecimal = 330,
			KPDivide = 331,
			KPMultiply = 332,
			KPSubtract = 333,
			KPAdd = 334,
			KPEnter = 335,
			KPEqual = 336,

			LeftShift = 340,
			LeftControl = 341,
			LeftAlt = 342,
			LeftSuper = 343,
			RightShift = 344,
			RightControl = 345,
			RightAlt = 346,
			RightSuper = 347,
			Menu = 348
		};
	}
}

#define VL_KEY_SPACE           ::Vinyl::Key::Space
#define VL_KEY_APOSTROPHE      ::Vinyl::Key::Apostrophe    /* ' */
#define VL_KEY_COMMA           ::Vinyl::Key::Comma         /* , */
#define VL_KEY_MINUS           ::Vinyl::Key::Minus         /* - */
#define VL_KEY_PERIOD          ::Vinyl::Key::Period        /* . */
#define VL_KEY_SLASH           ::Vinyl::Key::Slash         /* / */
#define VL_KEY_0               ::Vinyl::Key::D0
#define VL_KEY_1               ::Vinyl::Key::D1
#define VL_KEY_2               ::Vinyl::Key::D2
#define VL_KEY_3               ::Vinyl::Key::D3
#define VL_KEY_4               ::Vinyl::Key::D4
#define VL_KEY_5               ::Vinyl::Key::D5
#define VL_KEY_6               ::Vinyl::Key::D6
#define VL_KEY_7               ::Vinyl::Key::D7
#define VL_KEY_8               ::Vinyl::Key::D8
#define VL_KEY_9               ::Vinyl::Key::D9
#define VL_KEY_SEMICOLON       ::Vinyl::Key::Semicolon     /* ; */
#define VL_KEY_EQUAL           ::Vinyl::Key::Equal         /* = */
#define VL_KEY_A               ::Vinyl::Key::A
#define VL_KEY_B               ::Vinyl::Key::B
#define VL_KEY_C               ::Vinyl::Key::C
#define VL_KEY_D               ::Vinyl::Key::D
#define VL_KEY_E               ::Vinyl::Key::E
#define VL_KEY_F               ::Vinyl::Key::F
#define VL_KEY_G               ::Vinyl::Key::G
#define VL_KEY_H               ::Vinyl::Key::H
#define VL_KEY_I               ::Vinyl::Key::I
#define VL_KEY_J               ::Vinyl::Key::J
#define VL_KEY_K               ::Vinyl::Key::K
#define VL_KEY_L               ::Vinyl::Key::L
#define VL_KEY_M               ::Vinyl::Key::M
#define VL_KEY_N               ::Vinyl::Key::N
#define VL_KEY_O               ::Vinyl::Key::O
#define VL_KEY_P               ::Vinyl::Key::P
#define VL_KEY_Q               ::Vinyl::Key::Q
#define VL_KEY_R               ::Vinyl::Key::R
#define VL_KEY_S               ::Vinyl::Key::S
#define VL_KEY_T               ::Vinyl::Key::T
#define VL_KEY_U               ::Vinyl::Key::U
#define VL_KEY_V               ::Vinyl::Key::V
#define VL_KEY_W               ::Vinyl::Key::W
#define VL_KEY_X               ::Vinyl::Key::X
#define VL_KEY_Y               ::Vinyl::Key::Y
#define VL_KEY_Z               ::Vinyl::Key::Z
#define VL_KEY_LEFT_BRACKET    ::Vinyl::Key::LeftBracket   /* [ */
#define VL_KEY_BACKSLASH       ::Vinyl::Key::Backslash     /* \ */
#define VL_KEY_RIGHT_BRACKET   ::Vinyl::Key::RightBracket  /* ] */
#define VL_KEY_GRAVE_ACCENT    ::Vinyl::Key::GraveAccent   /* ` */
#define VL_KEY_WORLD_1         ::Vinyl::Key::World1        /* non-US #1 */
#define VL_KEY_WORLD_2         ::Vinyl::Key::World2        /* non-US #2 */

/* Function keys */
#define VL_KEY_ESCAPE          ::Vinyl::Key::Escape
#define VL_KEY_ENTER           ::Vinyl::Key::Enter
#define VL_KEY_TAB             ::Vinyl::Key::Tab
#define VL_KEY_BACKSPACE       ::Vinyl::Key::Backspace
#define VL_KEY_INSERT          ::Vinyl::Key::Insert
#define VL_KEY_DELETE          ::Vinyl::Key::Delete
#define VL_KEY_RIGHT           ::Vinyl::Key::Right
#define VL_KEY_LEFT            ::Vinyl::Key::Left
#define VL_KEY_DOWN            ::Vinyl::Key::Down
#define VL_KEY_UP              ::Vinyl::Key::Up
#define VL_KEY_PAGE_UP         ::Vinyl::Key::PageUp
#define VL_KEY_PAGE_DOWN       ::Vinyl::Key::PageDown
#define VL_KEY_HOME            ::Vinyl::Key::Home
#define VL_KEY_END             ::Vinyl::Key::End
#define VL_KEY_CAPS_LOCK       ::Vinyl::Key::CapsLock
#define VL_KEY_SCROLL_LOCK     ::Vinyl::Key::ScrollLock
#define VL_KEY_NUM_LOCK        ::Vinyl::Key::NumLock
#define VL_KEY_PRINT_SCREEN    ::Vinyl::Key::PrintScreen
#define VL_KEY_PAUSE           ::Vinyl::Key::Pause
#define VL_KEY_F1              ::Vinyl::Key::F1
#define VL_KEY_F2              ::Vinyl::Key::F2
#define VL_KEY_F3              ::Vinyl::Key::F3
#define VL_KEY_F4              ::Vinyl::Key::F4
#define VL_KEY_F5              ::Vinyl::Key::F5
#define VL_KEY_F6              ::Vinyl::Key::F6
#define VL_KEY_F7              ::Vinyl::Key::F7
#define VL_KEY_F8              ::Vinyl::Key::F8
#define VL_KEY_F9              ::Vinyl::Key::F9
#define VL_KEY_F10             ::Vinyl::Key::F10
#define VL_KEY_F11             ::Vinyl::Key::F11
#define VL_KEY_F12             ::Vinyl::Key::F12
#define VL_KEY_F13             ::Vinyl::Key::F13
#define VL_KEY_F14             ::Vinyl::Key::F14
#define VL_KEY_F15             ::Vinyl::Key::F15
#define VL_KEY_F16             ::Vinyl::Key::F16
#define VL_KEY_F17             ::Vinyl::Key::F17
#define VL_KEY_F18             ::Vinyl::Key::F18
#define VL_KEY_F19             ::Vinyl::Key::F19
#define VL_KEY_F20             ::Vinyl::Key::F20
#define VL_KEY_F21             ::Vinyl::Key::F21
#define VL_KEY_F22             ::Vinyl::Key::F22
#define VL_KEY_F23             ::Vinyl::Key::F23
#define VL_KEY_F24             ::Vinyl::Key::F24
#define VL_KEY_F25             ::Vinyl::Key::F25
/* Keypad */
#define VL_KEY_KP_0            ::Vinyl::Key::KP0
#define VL_KEY_KP_1            ::Vinyl::Key::KP1
#define VL_KEY_KP_2            ::Vinyl::Key::KP2
#define VL_KEY_KP_3            ::Vinyl::Key::KP3
#define VL_KEY_KP_4            ::Vinyl::Key::KP4
#define VL_KEY_KP_5            ::Vinyl::Key::KP5
#define VL_KEY_KP_6            ::Vinyl::Key::KP6
#define VL_KEY_KP_7            ::Vinyl::Key::KP7
#define VL_KEY_KP_8            ::Vinyl::Key::KP8
#define VL_KEY_KP_9            ::Vinyl::Key::KP9
#define VL_KEY_KP_DECIMAL      ::Vinyl::Key::KPDecimal
#define VL_KEY_KP_DIVIDE       ::Vinyl::Key::KPDivide
#define VL_KEY_KP_MULTIPLY     ::Vinyl::Key::KPMultiply
#define VL_KEY_KP_SUBTRACT     ::Vinyl::Key::KPSubtract
#define VL_KEY_KP_ADD          ::Vinyl::Key::KPAdd
#define VL_KEY_KP_ENTER        ::Vinyl::Key::KPEnter
#define VL_KEY_KP_EQUAL        ::Vinyl::Key::KPEqual
#define VL_KEY_LEFT_SHIFT      ::Vinyl::Key::LeftShift
#define VL_KEY_LEFT_CONTROL    ::Vinyl::Key::LeftControl
#define VL_KEY_LEFT_ALT        ::Vinyl::Key::LeftAlt
#define VL_KEY_LEFT_SUPER      ::Vinyl::Key::LeftSuper
#define VL_KEY_RIGHT_SHIFT     ::Vinyl::Key::RightShift
#define VL_KEY_RIGHT_CONTROL   ::Vinyl::Key::RightControl
#define VL_KEY_RIGHT_ALT       ::Vinyl::Key::RightAlt
#define VL_KEY_RIGHT_SUPER     ::Vinyl::Key::RightSuper
#define VL_KEY_MENU            ::Vinyl::Key::Menu