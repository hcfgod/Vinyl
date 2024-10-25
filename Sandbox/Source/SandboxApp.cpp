#include <Vinyl.h>
#include <Vinyl/Core/EntryPoint.h>

#include "Sandbox2D.h"

// Sandbox App
class Sandbox : public Vinyl::Application
{
public:
	Sandbox(const Vinyl::ApplicationSpecification& specification) : Vinyl::Application(specification)
	{
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};

Vinyl::Application* Vinyl::CreateApplication(Vinyl::ApplicationCommandLineArgs args)
{
	ApplicationSpecification spec;
	spec.Name = "Sandbox";
	spec.WorkingDirectory = "../Vinyl-Editor";
	spec.CommandLineArgs = args;

	return new Sandbox(spec);
}