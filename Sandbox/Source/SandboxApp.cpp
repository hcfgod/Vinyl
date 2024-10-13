#include <Vinyl.h>

class ExampleLayer : public Vinyl::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		
	}

	void OnEvent(Vinyl::Event& event) override
	{
		VL_TRACE("{0}", event.ToString());
	}
};

class Sandbox : public Vinyl::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Vinyl::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Vinyl::Application* Vinyl::CreateApplication()
{
	return new Sandbox();
}