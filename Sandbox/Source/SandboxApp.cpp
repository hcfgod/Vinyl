#include <Vinyl.h>

class ExampleLayer : public Vinyl::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		if (Vinyl::Input::IsKeyPressed(Vinyl::Key::Space))
		{
			VL_TRACE("Space has been pressed");
		}
	}

	void OnEvent(Vinyl::Event& event) override
	{
		
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