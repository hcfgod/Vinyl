#include <Vinyl.h>

#include "imgui/imgui.h"

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

	void OnImGuiRender() override
	{
		ImGui::Begin("Hello World");
		ImGui::End();
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
	}

	~Sandbox()
	{

	}
};

Vinyl::Application* Vinyl::CreateApplication()
{
	return new Sandbox();
}