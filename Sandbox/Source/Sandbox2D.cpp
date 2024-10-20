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
	rotation += timestep * m_RotationSpeed;

	VL_PROFILE_FUNCTION();

	// Update
	m_OrthographicCameraController.OnUpdate(timestep);

	// Reset render Statistics here
	Vinyl::Renderer2D::ResetStatistics();

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

	Vinyl::Renderer2D::BeginScene(m_OrthographicCameraController.GetCamera());

	// Draw grid
	float spacing = 1.5f; // Spacing between quads
	for (int y = 0; y < m_GridSize; ++y)
	{
		for (int x = 0; x < m_GridSize; ++x)
		{
			// Calculate position for each quad in the grid
			glm::vec2 position = { x * spacing - (m_GridSize * spacing) / 2.0f, y * spacing - (m_GridSize * spacing) / 2.0f };
			glm::vec4 color = { (x + 5.0f) / 10.0f, 0.3f, (y + 5.0f) / 10.0f, 0.5f };

			if (m_UseTexture)
			{	
				// Draw textured quad
				Vinyl::Renderer2D::DrawQuad({ position.x, position.y, 0.0f }, { 0.8f, 0.8f }, m_SqaureTexture, color);
			}
			else
			{
				// Draw colored quad
				Vinyl::Renderer2D::DrawQuad({ position.x, position.y, 0.0f }, { 0.8f, 0.8f }, color);
			}
		}
	}

	Vinyl::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	VL_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = Vinyl::Renderer2D::GetStatistics();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quad Count: %d", stats.QuadCount);
	ImGui::Text("Total Vertex Count: %d", stats.GetTotalVertexCount());
	ImGui::Text("Total Index Count: %d", stats.GetTotalIndexCount());

	// Grid settings
	ImGui::SliderInt("Grid Size", &m_GridSize, 1, 50); // Slider to change grid size
	ImGui::SliderFloat("Rotation Speed", &m_RotationSpeed, 0.0f, 100.0f); // Slider for rotation speed
	ImGui::Checkbox("Use Texture", &m_UseTexture); // Toggle between texture and color

	// Color picker for the square color
	ImGui::ColorEdit4("SqaureColor", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(Vinyl::Event& event)
{
	VL_PROFILE_FUNCTION();

	m_OrthographicCameraController.OnEvent(event);
}