#pragma once

#include "Core.h"
#include "Window.h"

#include "Vinyl/LayerStack.h"

#include "Events/Event.h"
#include "Vinyl/Events/ApplicationEvent.h"

namespace Vinyl
{
	class VINYL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in client
	Application* CreateApplication();
}