#include <Vinyl.h>

class ExampleLayer : public Vinyl::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		VL_TRACE("ExampleLayer::Update");
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
	}

	~Sandbox()
	{

	}
};

Vinyl::Application* Vinyl::CreateApplication()
{
	return new Sandbox();
}