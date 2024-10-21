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
		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
		Ref<Texture2D> m_BabyTexture;
		Ref<Texture2D> m_SpriteSheet;
		Ref<SubTexture2D> m_TreeTexture;
		Ref<Framebuffer> m_FrameBuffer;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

		// Grid customization parameters
		int m_GridSize = 5;             // Grid dimension, i.e., number of quads per row/column
		float m_RotationSpeed = 50.0f;  // Speed of rotation
		bool m_UseTexture = true;
	};
}