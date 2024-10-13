#include "vlpch.h"
#include "Application.h"

#include "Vinyl/Events/ApplicationEvent.h"
#include "Log.h"

namespace Vinyl
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		VL_TRACE(e.ToString());
		while (true);
	}
}