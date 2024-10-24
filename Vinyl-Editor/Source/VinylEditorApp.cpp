#include "EditorLayer.h"
#include "Vinyl/Core/EntryPoint.h"

namespace Vinyl
{
	// Sandbox App
	class VinylEditor : public Vinyl::Application
	{
	public:
		VinylEditor(ApplicationCommandLineArgs args) : Application("Vinyl Editor", args)
		{
			PushLayer(new EditorLayer());
		}

		~VinylEditor()
		{

		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new VinylEditor(args);
	}
}