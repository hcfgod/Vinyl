#include "EditorLayer.h"

namespace Vinyl
{
	EditorLayer::EditorLayer() : Layer("EditorLayer"), m_OrthographicCameraController(1280.0f / 720.0f) {}

	void EditorLayer::OnAttach()
	{
		VL_PROFILE_FUNCTION();

		m_BabyTexture = Vinyl::Texture2D::Create("Assets/Textures/baby.jpg");
		m_SpriteSheet = Vinyl::Texture2D::Create("Assets/Textures/RPGpack_sheet_2X.png");
		m_TreeTexture = Vinyl::SubTexture2D::CreateFromCoords(m_SpriteSheet, glm::vec2(2, 1), glm::vec2(128, 128), glm::vec2(1, 2));

		m_OrthographicCameraController.SetZoomLevel(5.0f);

		Vinyl::FramebufferSpecification frameBufferSpec;
		frameBufferSpec.Width = 1280;
		frameBufferSpec.Height = 720;

		m_FrameBuffer = Vinyl::Framebuffer::Create(frameBufferSpec);
	}

	void EditorLayer::OnDetach()
	{
		VL_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Vinyl::TimeStep timestep)
	{
		static float rotation = 0.0f;
		rotation += timestep * m_RotationSpeed;

		VL_PROFILE_FUNCTION();

		m_FrameBuffer->Bind();

		// Update
		m_OrthographicCameraController.OnUpdate(timestep);

		// Reset render Statistics here
		Vinyl::Renderer2D::ResetStatistics();

		// Render
		Vinyl::RenderCommand::SetClearColor(glm::vec4(0.1, 0.1, 0.1, 1.0));
		Vinyl::RenderCommand::Clear();

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

		Vinyl::Renderer2D::BeginScene(m_OrthographicCameraController.GetCamera());

		Vinyl::Renderer2D::DrawQuad({ 0.0f, 1.0f }, { 1.0f, 1.0f }, m_BabyTexture);
		Vinyl::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_TreeTexture);

		Vinyl::Renderer2D::EndScene();

		m_FrameBuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender()
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

			//Settings
			ImGui::Begin("Settings");

			auto stats = Vinyl::Renderer2D::GetStatistics();
			ImGui::Text("Renderer2D Stats:");
			ImGui::Text("Draw Calls: %d", stats.DrawCalls);
			ImGui::Text("Quads: %d", stats.QuadCount);
			ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
			ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
			ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

			ImGui::End();

			//Viewport
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
			ImGui::Begin("Viewport");
			ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
			
			uint32_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
			ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

			if (m_ViewportSize != *((glm::vec2*)&viewportPanelSize))
			{
				m_FrameBuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
				m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

				m_OrthographicCameraController.OnResize(viewportPanelSize.x, viewportPanelSize.y);
			}

			ImGui::End();
			ImGui::PopStyleVar();

			// End of dockspace
			ImGui::End();
		}
	}

	void EditorLayer::OnEvent(Vinyl::Event& event)
	{
		VL_PROFILE_FUNCTION();

		m_OrthographicCameraController.OnEvent(event);
	}
}