#pragma once

#include "Core.h"
#include "Window.h"

#include "Vinyl/Layer/LayerStack.h"

#include "Events/Event.h"
#include "Vinyl/Events/ApplicationEvent.h"
#include "Vinyl/ImGui/ImGuiLayer.h"
#include "Vinyl/Rendering/Shader.h"
#include "Vinyl/Rendering/Buffer.h"
#include "Vinyl/Rendering/VertexArray.h"

namespace Vinyl
{
	class VINYL_API Application
	{
	public:
		Application();
		virtual ~Application();

		static Application& Get() { return *s_Instance; }

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_SquareShader;
		std::shared_ptr<VertexArray> m_SquareVertexArray;
	private:
		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();
}