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

		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& path);
		void SaveSceneAs();
	private:
		Ref<Framebuffer> m_FrameBuffer;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2] = {};
		bool m_ViewportFocused = false, m_ViewportHovered = false;

		Ref<Scene> m_ActiveScene;

		Entity m_HoveredEntity;

		bool m_MainCamera = true;
		EditorCamera m_EditorCamera;

		int m_GizmoType = -1;

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
		ContentBrowserPanel m_ContentBrowserPanel;
	};
}