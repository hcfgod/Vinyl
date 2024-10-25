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
	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;
		const char* operator[](int index) const
		{
			VL_CORE_ASSERT(index < Count, "index < Count");
			return Args[index];
		}
	};

	struct ApplicationSpecification
	{
		std::string Name = "Vinyl Application";
		std::string WorkingDirectory;
		ApplicationCommandLineArgs CommandLineArgs;
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& specification);
		virtual ~Application();

		static Application& Get() { return *s_Instance; }

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Run();
		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
		Window& GetWindow() { return *m_Window; }

		const ApplicationSpecification& GetSpecification() const { return m_Specification; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		ApplicationSpecification m_Specification;

		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true; 
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication(ApplicationCommandLineArgs args);
}