#pragma once

#ifdef VL_PLATFORM_WINDOWS

extern Vinyl::Application* Vinyl::CreateApplication();

int main(int argc, char** argv)
{
	Vinyl::Log::Init();
	VL_CORE_INFO("Initialized Core Logger");
	VL_INFO("Initialized Client Logger");

	auto app = Vinyl::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif