#include "EditorLayer.h"

#include "Vinyl/Scene/SceneSerializer.h"

#include <glm/gtc/type_ptr.hpp>

namespace Vinyl
{
	EditorLayer::EditorLayer() : Layer("EditorLayer"), m_OrthographicCameraController(1280.0f / 720.0f) {}

	void EditorLayer::OnAttach()
	{
		VL_PROFILE_FUNCTION();

		m_OrthographicCameraController.SetZoomLevel(5.0f);

		FramebufferSpecification frameBufferSpec;
		frameBufferSpec.Width = 1280;
		frameBufferSpec.Height = 720;

		m_FrameBuffer = Framebuffer::Create(frameBufferSpec);

		m_ActiveScene = CreateRef<Scene>();

#if 0
		auto coloredSquare = m_ActiveScene->CreateEntity("Colored Square - 1");
		coloredSquare.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });
		m_SquareEntity = coloredSquare;

		auto coloredSquare2 = m_ActiveScene->CreateEntity("Colored Square - 2");
		coloredSquare2.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.25f, 0.35f, 0.65f, 1.0f });

		m_CameraEntity = m_ActiveScene->CreateEntity("Camera A");
		auto& mainCamera = m_CameraEntity.AddComponent<CameraComponent>();
		mainCamera.MainCamera = true;

		m_SecondCamera = m_ActiveScene->CreateEntity("Camera B");
		auto& cc = m_SecondCamera.AddComponent<CameraComponent>();
		cc.MainCamera = false;

		class CameraController : public ScriptableEntity
		{
		public:
			void OnCreate()
			{
				auto& translation = GetComponent<TransformComponent>().Translation;
				translation.x = rand() % 10 - 5.0f;
			}
			void OnDestroy()
			{
			}
			void OnUpdate(TimeStep timestep)
			{
				auto& translation = GetComponent<TransformComponent>().Translation;
				float speed = 5.0f;
				if (Input::IsKeyPressed(Key::A))
					translation.x -= speed * timestep;
				if (Input::IsKeyPressed(Key::D))
					translation.x += speed * timestep;
				if (Input::IsKeyPressed(Key::W))
					translation.y += speed * timestep;
				if (Input::IsKeyPressed(Key::S))
					translation.y -= speed * timestep;
			}
		};
		m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
#endif

		m_SceneHierarchyPanel.SetContext(m_ActiveScene);
	}

	void EditorLayer::OnDetach()
	{
		VL_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(TimeStep timestep)
	{
		VL_PROFILE_FUNCTION();

		// Update

		if(m_ViewportFocused && m_ViewportHovered)
			m_OrthographicCameraController.OnUpdate(timestep);

		FramebufferSpecification spec = m_FrameBuffer->GetSpecification();
		if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y)) // zero sized framebuffer is invalid
		{
			m_FrameBuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_OrthographicCameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);

			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}

		// Render
		
		Renderer2D::ResetStatistics(); // Reset render Statistics here

		m_FrameBuffer->Bind();

		RenderCommand::SetClearColor(glm::vec4(0.1, 0.1, 0.1, 1.0));
		RenderCommand::Clear();

		m_ActiveScene->OnUpdate(timestep);

		m_FrameBuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender()
	{
		VL_PROFILE_FUNCTION();

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

		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 370.0f;

		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		style.WindowMinSize.x = minWinSizeX;

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);
	
				if (ImGui::MenuItem("Serialize"))
				{
					SceneSerializer sceneSerializer(m_ActiveScene);
					sceneSerializer.Serialize("Assets/Scenes/Example.Vinyl");
				}

				if (ImGui::MenuItem("Deserialize"))
				{
					SceneSerializer sceneSerializer(m_ActiveScene);
					sceneSerializer.Deserialize("Assets/Scenes/Example.Vinyl");
				}

				if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		m_SceneHierarchyPanel.OnImGuiRender();

		//Settings
		ImGui::Begin("Renderer2D Stats");

		auto stats = Renderer2D::GetStatistics();
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::End();

		//Viewport
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->SetBlockEvents(!m_ViewportFocused || !m_ViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		uint64_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
		ImGui::Image(reinterpret_cast<void*>(static_cast<uintptr_t>(textureID)), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		ImGui::End();
		ImGui::PopStyleVar();

		// End of dockspace
		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		VL_PROFILE_FUNCTION();

		m_OrthographicCameraController.OnEvent(event);
	}
}