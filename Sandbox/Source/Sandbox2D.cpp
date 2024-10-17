#include "Sandbox2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_OrthographicCameraController(1280.0f / 720.0f) {}

void Sandbox2D::OnAttach()
{
	m_SquareVertexArray = Vinyl::VertexArray::Create();

	float vertices[3 * 4] =
	{
		-0.50f, -0.50f, -0.0f,
		 0.50f, -0.50f, -0.0f,
		 0.50f,  0.50f, -0.0f,
		-0.50f,  0.50f, -0.0f
	};

	uint32_t indices[6] =
	{
		0, 1, 2,
		2, 3, 0,
	};

	Vinyl::Ref<Vinyl::VertexBuffer> squareVertexBuffer(Vinyl::VertexBuffer::Create(vertices, sizeof(vertices)));

	squareVertexBuffer->SetLayout
	({
		{ Vinyl::ShaderDataType::Float3, "a_Position" }
	});
	m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

	Vinyl::Ref<Vinyl::IndexBuffer> squareIndexBuffer(Vinyl::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
	m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

	m_FlatColorShader = Vinyl::Shader::Create("FlatColor", "Assets/Shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach() {}

void Sandbox2D::OnUpdate(Vinyl::TimeStep timestep)
{
	// Update
	m_OrthographicCameraController.OnUpdate(timestep);

	// Render
	Vinyl::RenderCommand::SetClearColor(glm::vec4(0.1, 0.1, 0.1, 1.0));
	Vinyl::RenderCommand::Clear();

	Vinyl::Renderer::BeginScene(m_OrthographicCameraController.GetCamera());

	std::dynamic_pointer_cast<Vinyl::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Vinyl::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Vinyl::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

	Vinyl::Renderer::EndScene();
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