#pragma once
#include "Vinyl/Core/Application.h"

#ifdef VL_PLATFORM_WINDOWS

extern Vinyl::Application* Vinyl::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	Vinyl::Log::Init();
	
	VL_PROFILE_BEGIN_SESSION("Startup", "VinylProfile-Startup.json");
	auto app = Vinyl::CreateApplication({ argc, argv });
	VL_PROFILE_END_SESSION();

	VL_PROFILE_BEGIN_SESSION("Runtime", "VinylProfile-Runtime.json");
	app->Run();
	VL_PROFILE_END_SESSION();

	VL_PROFILE_BEGIN_SESSION("Shutdown", "VinylProfile-Shutdown.json");
	delete app;
	VL_PROFILE_END_SESSION();

	return 0;
}

#endif