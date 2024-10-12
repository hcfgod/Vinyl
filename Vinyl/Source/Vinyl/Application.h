#pragma once

#include "Core.h"

namespace Vinyl
{
	class VINYL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in client
	Application* CreateApplication();
}