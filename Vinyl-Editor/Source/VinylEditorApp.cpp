#include "EditorLayer.h"
#include "Vinyl/Core/EntryPoint.h"

namespace Vinyl
{
	class VinylEditor : public Vinyl::Application
	{
	public:
		VinylEditor(const Vinyl::ApplicationSpecification& specification) : Vinyl::Application(specification)
		{
			PushLayer(new EditorLayer());
		}

		~VinylEditor()
		{

		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification spec;
		spec.Name = "Vinyl Editor";
		spec.CommandLineArgs = args;

		return new VinylEditor(spec);
	}
}