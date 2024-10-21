#pragma once
#include <Vinyl.h>

class Sandbox2D : public Vinyl::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(Vinyl::TimeStep timestep) override;

	void OnImGuiRender() override;

	void OnEvent(Vinyl::Event& event) override;
private:
	Vinyl::OrthographicCameraController m_OrthographicCameraController;
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	Vinyl::Ref<Vinyl::Texture2D> m_BabyTexture;
	Vinyl::Ref<Vinyl::Texture2D> m_SpriteSheet;
	Vinyl::Ref<Vinyl::SubTexture2D> m_WaterTexture;
	Vinyl::Ref<Vinyl::SubTexture2D> m_DirtTexture;
	Vinyl::Ref<Vinyl::SubTexture2D> m_TreeTexture;

	// Grid customization parameters
	int m_GridSize = 5;             // Grid dimension, i.e., number of quads per row/column
	float m_RotationSpeed = 50.0f;  // Speed of rotation
	bool m_UseTexture = true;

	uint32_t m_MapWidth = 0, m_MapHeight = 0;
	std::unordered_map<char, Vinyl::Ref<Vinyl::SubTexture2D>> s_TextureMap;
};