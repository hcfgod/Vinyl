#include "Sandbox2D.h"

static const uint32_t s_MapWidth = 50;
static const char* s_MapTiles =
"wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"
"wwddddddddddwwwwwwwwwwwwwwwwwwddddddddddwwwww"
"wddddddddddddddddwwwwwwwwwwwddddddddddddddddw"
"wdddddwwwwdddddddwwwwwwwwwwdddddddddwwwwddddw"
"wdddddwwwwdddddddddwwwwwdddddddddddwwwwwddddw"
"wdddddddwwdddddddddddddddddddddddwwwwwwwddddw"
"wddddddddddddddwwwwwwwwwwwwwwwwddddddwwwwwddd"
"wddddddddddddwwwwwwwwwwwwwwwwwwwddddddddddddw"
"wdddddddddddddwwwwwwddddddddddddddddddwwwwwww"
"wdddddddddwwwwwwwwdddddddddddddwwwwwwwwwwwwww"
"wwwwddddddddddwwwwwwwwdddddddwwwwwwwwwwwwwwww"
"wwwwwwdddddddddddddddddddddddwwwwwwwwwwwwwwww"
"wwwwwwwwwwwwddddddddddddddddddddddddddddwwwww"
"wwwwwwwwwwwwwddddddddddccdddddwwwwwwddddddddd"
"wwwwwwwwwwwwwwwwwwdddddddddddwwwwwwwwwddddddd"
"wwwwwwwwwwwwwwwwwwwwwwddddddddddddddddddddddd"
"wwwwwwwwwwwwwwwwwwwwwwwdddddddddddddddddddddd"
"wwwwwwwwwwwwwwwwwwwwwwwwwwddddddddddddddddddd"
"wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwdddddddddddddww"
"wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwdddddddww"
"wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwddddddd"
"wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwdddddd"
"wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"
"wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"
"wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww";

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_OrthographicCameraController(1280.0f / 720.0f) {}

void Sandbox2D::OnAttach()
{
	VL_PROFILE_FUNCTION();

	m_BabyTexture = Vinyl::Texture2D::Create("Assets/Textures/baby.jpg");
	m_SpriteSheet = Vinyl::Texture2D::Create("Assets/Textures/RPGpack_sheet_2X.png");

	s_TextureMap['w'] = Vinyl::SubTexture2D::CreateFromCoords(m_SpriteSheet, glm::vec2(11, 11), glm::vec2(128, 128));
	s_TextureMap['d'] = Vinyl::SubTexture2D::CreateFromCoords(m_SpriteSheet, glm::vec2(6, 11), glm::vec2(128, 128));

	m_TreeTexture = Vinyl::SubTexture2D::CreateFromCoords(m_SpriteSheet, glm::vec2(2, 1), glm::vec2(128, 128), glm::vec2(1, 2));

	m_MapWidth = s_MapWidth;
	m_MapHeight = strlen(s_MapTiles) / s_MapWidth;

	m_OrthographicCameraController.SetZoomLevel(5.0f);
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

	#if OldRenderTest
		Vinyl::Renderer2D::BeginScene(m_OrthographicCameraController.GetCamera());

		Vinyl::Renderer2D::DrawRotatedQuad({ 1.5f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), m_SquareColor);
		Vinyl::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, m_SquareColor);
		Vinyl::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Vinyl::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_BabyTexture);
		Vinyl::Renderer2D::DrawRotatedQuad({ -2.5f, 0.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(rotation), m_BabyTexture, 5.0f);

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
					Vinyl::Renderer2D::DrawQuad({ position.x, position.y, 0.0f }, { 0.8f, 0.8f }, m_BabyTexture, color);
				}
				else
				{
					// Draw colored quad
					Vinyl::Renderer2D::DrawQuad({ position.x, position.y, 0.0f }, { 0.8f, 0.8f }, color);
				}
			}
		}

		Vinyl::Renderer2D::EndScene();

	#endif

	Vinyl::Renderer2D::BeginScene(m_OrthographicCameraController.GetCamera());

	for (uint32_t y = 0; y < m_MapHeight; y++)
	{
		for (uint32_t x = 0; x < m_MapWidth; x++)
		{
			char tileType = s_MapTiles[x + y * m_MapWidth];
			Vinyl::Ref<Vinyl::SubTexture2D> texture;

			if (s_TextureMap.find(tileType) != s_TextureMap.end())
			{
				texture = s_TextureMap[tileType];
			}
			else
			{
				texture = m_TreeTexture;
			}

			Vinyl::Renderer2D::DrawQuad({ x - m_MapWidth / 2.0f, m_MapHeight - y - m_MapHeight / 2.0f, 0.5f }, { 1.0f, 1.0f }, texture);
		}
	}

	Vinyl::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	VL_PROFILE_FUNCTION();

	static bool dockingEnabled = true;
	if (dockingEnabled)
	{
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Exit")) Vinyl::Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");

		auto stats = Vinyl ::Renderer2D::GetStatistics();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

		uint32_t textureID = m_BabyTexture->GetRendererID();
		ImGui::Image((void*)textureID, ImVec2{ 256.0f, 256.0f }, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();

		// End of dockspace
		ImGui::End();
	}
	else
	{
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
}

void Sandbox2D::OnEvent(Vinyl::Event& event)
{
	VL_PROFILE_FUNCTION();

	m_OrthographicCameraController.OnEvent(event);
}