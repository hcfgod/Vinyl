#include <Vinyl.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Vinyl::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_SquareVertexArray.reset(Vinyl::VertexArray::Create());

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

		m_FlatColorShader.reset(Vinyl::Shader::Create(flatColorVertexSource, flatColorFragmentSource));


		std::string textureVertexSource =
		R"(
				#version 330 core

				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec2 a_TextureCoord;

				out vec2 v_TextureCoord;

				uniform mat4 u_ViewProjection;
				uniform mat4 u_Transform;

				void main()
				{
					v_TextureCoord = a_TextureCoord;
					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
				}
		)";

		std::string textureFragmentSource =
		R"(
				#version 330 core

				in vec2 v_TextureCoord;

				out vec4 o_Color;
				
				uniform sampler2D u_Texture;

				void main()
				{			
					o_Color = texture(u_Texture, v_TextureCoord);
				}
		)";

		m_TextureShader.reset(Vinyl::Shader::Create(textureVertexSource, textureFragmentSource));
		m_SqaureTexture = Vinyl::Texture2D::Create("../Assets/Textures/baby.jpg");

		std::dynamic_pointer_cast<Vinyl::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Vinyl::TimeStep timestep) override
	{
		float deltaTime = timestep;
		HandleCameraInput(deltaTime);

		Vinyl::RenderCommand::SetClearColor(glm::vec4(0.1, 0.1, 0.1, 1.0));
		Vinyl::RenderCommand::Clear();

		m_OrthographicCamera.SetPosition(m_CameraPosition);
		m_OrthographicCamera.SetRotation(m_CameraRotation);

		Vinyl::Renderer::BeginScene(m_OrthographicCamera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Vinyl::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Vinyl::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Vinyl::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, transform);
			}
		}

		m_SqaureTexture->Bind();
		Vinyl::Renderer::Submit(m_TextureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Vinyl::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");

		ImGui::ColorEdit3("SqaureColor", glm::value_ptr(m_SquareColor));

		ImGui::End();
	}

	void OnEvent(Vinyl::Event& event) override {}

	void HandleCameraInput(float deltaTime)
	{
		if (Vinyl::Input::IsKeyPressed(Vinyl::Key::W))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * deltaTime;
		}
		else if (Vinyl::Input::IsKeyPressed(Vinyl::Key::S))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * deltaTime;
		}

		if (Vinyl::Input::IsKeyPressed(Vinyl::Key::A))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * deltaTime;
		}
		else if (Vinyl::Input::IsKeyPressed(Vinyl::Key::D))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * deltaTime;
		}

		if (Vinyl::Input::IsKeyPressed(Vinyl::Key::R))
		{
			m_CameraRotation += m_CameraRotationSpeed * deltaTime;
		}

		if (Vinyl::Input::IsKeyPressed(Vinyl::Key::T))
		{
			m_CameraRotation -= m_CameraRotationSpeed * deltaTime;
		}
	}
private:
	Vinyl::Ref<Vinyl::Shader> m_FlatColorShader;
	Vinyl::Ref<Vinyl::Shader> m_TextureShader;
	Vinyl::Ref<Vinyl::VertexArray> m_SquareVertexArray;

	Vinyl::Ref<Vinyl::Texture> m_SqaureTexture;

	Vinyl::OrthographicCamera m_OrthographicCamera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 2.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

// Sandbox App
class Sandbox : public Vinyl::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Vinyl::Application* Vinyl::CreateApplication()
{
	return new Sandbox();
}