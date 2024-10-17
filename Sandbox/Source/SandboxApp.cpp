#include <Vinyl.h>
#include <Vinyl/Core/EntryPoint.h>

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public Vinyl::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_OrthographicCameraController(1280.0f / 720.0f)
	{
		m_SquareVertexArray = Vinyl::VertexArray::Create();

		float vertices[5 * 4] =
		{
			-0.50f, -0.50f, -0.0f, 0.0f, 0.0f,
			 0.50f, -0.50f, -0.0f, 1.0f, 0.0f,
			 0.50f,  0.50f, -0.0f, 1.0f, 1.0f,
			-0.50f,  0.50f, -0.0f, 0.0f, 1.0f,
		};

		uint32_t indices[6] =
		{
			0, 1, 2,
			2, 3, 0,
		};

		Vinyl::Ref<Vinyl::VertexBuffer> squareVertexBuffer(Vinyl::VertexBuffer::Create(vertices, sizeof(vertices)));

		squareVertexBuffer->SetLayout
		({
			{ Vinyl::ShaderDataType::Float3, "a_Position" },
			{ Vinyl::ShaderDataType::Float2, "a_TextureCoords" }
		});
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		Vinyl::Ref<Vinyl::IndexBuffer> squareIndexBuffer(Vinyl::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

		std::string flatColorVertexSource =
			R"(
				#version 330 core

				layout(location = 0) in vec3 a_Position;

				out vec3 v_Position;
	
				uniform mat4 u_ViewProjection;
				uniform mat4 u_Transform;

				void main()
				{
					v_Position = a_Position;

					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
				}
		  )";

		std::string flatColorFragmentSource =
			R"(
				#version 330 core

				in vec3 v_Position;

				out vec4 o_Color;
				
				uniform vec3 u_Color;

				void main()
				{
					o_Color = vec4(u_Color, 1.0f);
				}
		  )";

		m_FlatColorShader = Vinyl::Shader::Create("FlatColor", flatColorVertexSource, flatColorFragmentSource);
		auto simpleTextureShader = m_ShaderLibrary.Load("SimpleTexture", "Assets/Shaders/Texture.glsl");

		m_SqaureTexture = Vinyl::Texture2D::Create("Assets/Textures/baby.jpg");
		m_SilkTexture = Vinyl::Texture2D::Create("Assets/Textures/silk.png");

		simpleTextureShader->SetInt("u_Texture", 0);
	}

	void OnUpdate(Vinyl::TimeStep timestep) override
	{
		// Update
		m_OrthographicCameraController.OnUpdate(timestep);

		// Render
		Vinyl::RenderCommand::SetClearColor(glm::vec4(0.1, 0.1, 0.1, 1.0));
		Vinyl::RenderCommand::Clear();

		Vinyl::Renderer::BeginScene(m_OrthographicCameraController.GetCamera());
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		m_FlatColorShader->Bind();
		m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Vinyl::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, transform);
			}
		}

		auto simpleTextureShader = m_ShaderLibrary.Get("SimpleTexture");
		m_SqaureTexture->Bind();
		Vinyl::Renderer::Submit(simpleTextureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(2.0f)));

		m_SilkTexture->Bind();
		Vinyl::Renderer::Submit(simpleTextureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(0.2f)));

		Vinyl::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");

		ImGui::ColorEdit3("SqaureColor", glm::value_ptr(m_SquareColor));

		ImGui::End();
	}

	void OnEvent(Vinyl::Event& event) override
	{
		m_OrthographicCameraController.OnEvent(event);
	}
private:
	Vinyl::ShaderLibrary m_ShaderLibrary;
	Vinyl::Ref<Vinyl::Shader> m_FlatColorShader;

	Vinyl::Ref<Vinyl::VertexArray> m_SquareVertexArray;

	Vinyl::Ref<Vinyl::Texture> m_SqaureTexture, m_SilkTexture;

	Vinyl::OrthographicCameraController m_OrthographicCameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

// Sandbox App
class Sandbox : public Vinyl::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};

Vinyl::Application* Vinyl::CreateApplication()
{
	return new Sandbox();
}