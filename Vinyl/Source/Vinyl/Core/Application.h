#pragma once

#include "Vinyl/Core/Base.h"
#include "Vinyl/Core/Window.h"

#include "Vinyl/Core/Layer/LayerStack.h"

#include "Vinyl/Events/Event.h"
#include "Vinyl/Events/ApplicationEvent.h"

#include "Vinyl/ImGui/ImGuiLayer.h"

#include "Vinyl/Core/TimeStep.h"

namespace Vinyl
{
	class Application
	{
	public:
		Application(const std::string& name = "Vinyl App");
		virtual ~Application();

		static Application& Get() { return *s_Instance; }

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Run();
		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
		Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true; 
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();
}