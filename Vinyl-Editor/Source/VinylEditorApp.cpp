#include "EditorLayer.h"
#include "Vinyl/Core/EntryPoint.h"

namespace Vinyl
{
	// Sandbox App
	class VinylEditor : public Vinyl::Application
	{
	public:
		VinylEditor() : Application("Vinyl Editor")
		{
			PushLayer(new EditorLayer());
		}

		~VinylEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new VinylEditor();
	}
}