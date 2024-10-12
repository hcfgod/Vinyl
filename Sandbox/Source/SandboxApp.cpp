#include <Vinyl.h>

class Sandbox : public Vinyl::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Vinyl::Application* Vinyl::CreateApplication()
{
	return new Sandbox();
}