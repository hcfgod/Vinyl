#include <Vinyl.h>

#include "imgui/imgui.h"

class ExampleLayer : public Vinyl::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Vinyl::VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, -0.0f, 0.2f, 0.4f, 1.0f, 1.0f,
			 0.5f, -0.5f, -0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, -0.0f, 0.5f, 0.3f, 1.0f, 1.0f
		};

		std::shared_ptr<Vinyl::VertexBuffer> vertexBuffer(Vinyl::VertexBuffer::Create(vertices, sizeof(vertices)));

		Vinyl::BufferLayout layout
		{
			{ Vinyl::ShaderDataType::Float3, "a_Position" },
			{ Vinyl::ShaderDataType::Float4, "a_Color" },
		};
		vertexBuffer->SetLayout(layout);
		// Add the VertexBuffer to the VertexArray after the VertexBuffer has been setup and a layout has been added to the VertexBuffer
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] =
		{
			0, 1, 2,
		};

		std::shared_ptr<Vinyl::IndexBuffer> indexBuffer(Vinyl::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVertexArray.reset(Vinyl::VertexArray::Create());

		float vertices2[3 * 4] =
		{
			-0.55f, -0.55f, -0.0f,
			 0.55f, -0.55f, -0.0f,
			 0.55f,  0.55f, -0.0f,
			-0.55f,  0.55f, -0.0f
		};

		uint32_t indices2[6] =
		{
			0, 1, 2,
			2, 3, 0,
		};

		std::shared_ptr<Vinyl::VertexBuffer> squareVertexBuffer(Vinyl::VertexBuffer::Create(vertices2, sizeof(vertices2)));

		squareVertexBuffer->SetLayout
		({
			{ Vinyl::ShaderDataType::Float3, "a_Position" }
		});
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		std::shared_ptr<Vinyl::IndexBuffer> squareIndexBuffer(Vinyl::IndexBuffer::Create(indices2, sizeof(indices2) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

		std::string vertexSource =
			R"(
				#version 330 core

				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;

				out vec3 v_Position;
				out vec4 v_Color;

				uniform mat4 u_ViewProjection;

				void main()
				{
					v_Position = a_Position;
					v_Color = a_Color;

					gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
				}
		  )";

		std::string fragmentSource =
			R"(
				#version 330 core

				in vec3 v_Position;
				in vec4 v_Color;
				out vec4 o_Color;
				
				void main()
				{
					o_Color = v_Color;
				}
		  )";

		m_Shader.reset(new Vinyl::Shader(vertexSource, fragmentSource));

		std::string squareVertexSource =
			R"(
				#version 330 core

				layout(location = 0) in vec3 a_Position;
	
				out vec3 v_Position;
	
				uniform mat4 u_ViewProjection;

				void main()
				{
					v_Position = a_Position;

					gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
				}
		  )";

		std::string squareFragmentSource =
			R"(
				#version 330 core

				in vec3 v_Position;

				out vec4 o_Color;
				
				void main()
				{
					o_Color = vec4(0.25, 0.25, 0.25, 1.0);
				}
		  )";

		m_SquareShader.reset(new Vinyl::Shader(squareVertexSource, squareFragmentSource));
	}

	void OnUpdate() override
	{
		HandleCamera();

		Vinyl::RenderCommand::SetClearColor(glm::vec4(0.1, 0.1, 0.1, 1.0));
		Vinyl::RenderCommand::Clear();

		m_OrthographicCamera.SetPosition(m_CameraPosition);
		m_OrthographicCamera.SetRotation(m_CameraRotation);

		Vinyl::Renderer::BeginScene(m_OrthographicCamera);

		Vinyl::Renderer::Submit(m_SquareShader, m_SquareVertexArray);
		Vinyl::Renderer::Submit(m_Shader, m_VertexArray);

		Vinyl::Renderer::EndScene();
	}

	void OnImGuiRender() override {}
	void OnEvent(Vinyl::Event& event) override {}

	void HandleCamera()
	{
		if (Vinyl::Input::IsKeyPressed(Vinyl::Key::W))
		{
			m_CameraPosition.y += m_CameraMoveSpeed;
		}
		else if (Vinyl::Input::IsKeyPressed(Vinyl::Key::S))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed;
		}

		if (Vinyl::Input::IsKeyPressed(Vinyl::Key::A))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed;
		}
		else if (Vinyl::Input::IsKeyPressed(Vinyl::Key::D))
		{
			m_CameraPosition.x += m_CameraMoveSpeed;
		}

		if (Vinyl::Input::IsKeyPressed(Vinyl::Key::R))
		{
			m_CameraRotation += m_CameraRotationSpeed;
		}

		if (Vinyl::Input::IsKeyPressed(Vinyl::Key::T))
		{
			m_CameraRotation -= m_CameraRotationSpeed;
		}
	}
private:
	std::shared_ptr<Vinyl::Shader> m_Shader;
	std::shared_ptr<Vinyl::VertexArray> m_VertexArray;

	std::shared_ptr<Vinyl::Shader> m_SquareShader;
	std::shared_ptr<Vinyl::VertexArray> m_SquareVertexArray;

	Vinyl::OrthographicCamera m_OrthographicCamera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.015f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 2.0f;
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