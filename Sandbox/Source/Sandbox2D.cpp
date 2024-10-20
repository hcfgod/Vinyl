#include "Sandbox2D.h"

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_OrthographicCameraController(1280.0f / 720.0f) {}

void Sandbox2D::OnAttach()
{
	VL_PROFILE_FUNCTION();

	m_SqaureTexture = Vinyl::Texture2D::Create("Assets/Textures/baby.jpg");
}

void Sandbox2D::OnDetach()
{
	VL_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Vinyl::TimeStep timestep)
{
	static float rotation = 0.0f;
	rotation += timestep * 50.0f;

	VL_PROFILE_FUNCTION();

	// Update
	m_OrthographicCameraController.OnUpdate(timestep);

	// Render
	Vinyl::RenderCommand::SetClearColor(glm::vec4(0.1, 0.1, 0.1, 1.0));
	Vinyl::RenderCommand::Clear();

	Vinyl::Renderer2D::BeginScene(m_OrthographicCameraController.GetCamera());

	Vinyl::Renderer2D::DrawRotatedQuad({ 1.5f, 0.0f }, { 0.8f, 0.8f }, -45.0f, m_SquareColor);
	Vinyl::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, m_SquareColor);
	Vinyl::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Vinyl::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_SqaureTexture);
	Vinyl::Renderer2D::DrawRotatedQuad({ -2.5f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_SqaureTexture, 5.0f);

	Vinyl::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	VL_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	ImGui::ColorEdit4("SqaureColor", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(Vinyl::Event& event)
{
	VL_PROFILE_FUNCTION();

	m_OrthographicCameraController.OnEvent(event);
}