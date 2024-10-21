#include <Vinyl.h>
#include <Vinyl/Core/EntryPoint.h>

#include "Sandbox2D.h"

// Sandbox App
class Sandbox : public Vinyl::Application
{
public:
	Sandbox()
	{
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};

Vinyl::Application* Vinyl::CreateApplication()
{
	return new Sandbox();
}