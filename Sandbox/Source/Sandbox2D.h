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
	Vinyl::Ref<Vinyl::Shader> m_FlatColorShader;

	Vinyl::Ref<Vinyl::VertexArray> m_SquareVertexArray;

	Vinyl::OrthographicCameraController m_OrthographicCameraController;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	Vinyl::Ref<Vinyl::Texture2D> m_SqaureTexture;
};