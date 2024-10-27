#pragma once
#include <Vinyl.h>

class Sandbox2D : public Vinyl::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(Vinyl::TimeStep timestep) override;

	void OnImGuiRender() override;

	void OnEvent(Vinyl::Event& event) override;
private:
};