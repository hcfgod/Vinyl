#pragma once

#ifdef VL_PLATFORM_WINDOWS

extern Vinyl::Application* Vinyl::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Vinyl::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif