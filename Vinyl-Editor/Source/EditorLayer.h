#pragma once
#include <Vinyl.h>
#include <Vinyl/Rendering/Camera/EditorCamera.h>

#include "Panels/SceneHierarchyPanel.h"
#include "Panels/ContentBrowserPanel.h"

namespace Vinyl
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate(TimeStep timestep) override;

		void OnImGuiRender() override;

		void OnEvent(Event& event) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& event);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& event);

		// Scene methods
		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& path);
		void SaveSceneAs();
		void SaveScene();

		void OnScenePlay();
		void OnSceneStop();

		// Dockspace
		void StartDockspace();
		void RenderInDockspace();
		void EndDockspace();

		// Gizmos
		void RenderGizmos();

		// UI Panels
		void MenuBar();
		void Viewport();
		void UI_Toolbar();
		void Renderer2DStats();

	private:
		EditorCamera m_EditorCamera;
		Ref<Framebuffer> m_FrameBuffer;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2] = {};
		bool m_ViewportFocused = false, m_ViewportHovered = false;

		Ref<Scene> m_ActiveScene;
		std::filesystem::path m_CurrentScenePath;

		Entity m_HoveredEntity;

		int m_GizmoType = -1;

		enum class SceneState
		{
			Edit = 0, Play = 1
		};
		SceneState m_SceneState = SceneState::Edit;

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
		ContentBrowserPanel m_ContentBrowserPanel;

		// Editor resources
		Ref<Texture2D> m_IconPlay, m_IconStop;
	};
}