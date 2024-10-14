#pragma once

#include "Core.h"
#include "Window.h"

#include "Vinyl/Layer/LayerStack.h"

#include "Events/Event.h"
#include "Vinyl/Events/ApplicationEvent.h"
#include "Vinyl/ImGui/ImGuiLayer.h"
#include "Vinyl/Renderer/Shader.h"
#include "Vinyl/Renderer/Buffer.h"

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

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();
}