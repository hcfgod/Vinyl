#pragma once
#include <Vinyl.h>

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
		OrthographicCameraController m_OrthographicCameraController;
		Ref<Framebuffer> m_FrameBuffer;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		bool m_ViewportFocused = false, m_ViewportHovered = false;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		bool m_MainCamera = true;
	};
}