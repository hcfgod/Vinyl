#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_OrthographicCameraController(1280.0f / 720.0f) {}

void Sandbox2D::OnAttach()
{
	m_SqaureTexture = Vinyl::Texture2D::Create("Assets/Textures/baby.jpg");
}

void Sandbox2D::OnDetach() {}

void Sandbox2D::OnUpdate(Vinyl::TimeStep timestep)
{
	// Update
	m_OrthographicCameraController.OnUpdate(timestep);

	// Render
	Vinyl::RenderCommand::SetClearColor(glm::vec4(0.1, 0.1, 0.1, 1.0));
	Vinyl::RenderCommand::Clear();

	Vinyl::Renderer2D::BeginScene(m_OrthographicCameraController.GetCamera());

	Vinyl::Renderer2D::DrawQuad({ -1.5f,  0.0f }, { 0.5f, 0.5f }, m_SquareColor);
	Vinyl::Renderer2D::DrawQuad({ -0.5f, -0.3f }, { 0.5f, 1.0f }, m_SquareColor);
	Vinyl::Renderer2D::DrawQuad({  1.0f,  0.0f, -0.1f }, { 10.0f, 10.0f }, m_SqaureTexture);

	Vinyl::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");

	ImGui::ColorEdit4("SqaureColor", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(Vinyl::Event& event)
{
	m_OrthographicCameraController.OnEvent(event);
}