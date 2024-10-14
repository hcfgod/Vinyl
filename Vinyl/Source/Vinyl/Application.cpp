#include "vlpch.h"
#include "Application.h"

#include "Input.h"

#include "Rendering/Renderer/Renderer.h"

namespace Vinyl
{
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		VL_CORE_ASSERT(!s_Instance, "Application already exist.");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_ImGuiLayer = new ImGuiLayer();

		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, -0.0f, 0.2f, 0.4f, 1.0f, 1.0f,
			 0.5f, -0.5f, -0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, -0.0f, 0.5f, 0.3f, 1.0f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout
		{
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
		};

		vertexBuffer->SetLayout(layout);
		// Add the VertexBuffer to the VertexArray after the VertexBuffer has been setup and a layout has been added to the VertexBuffer
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] =
		{
			0, 1, 2,
		};

		std::shared_ptr<IndexBuffer> indexBuffer(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVertexArray.reset(VertexArray::Create());

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

		std::shared_ptr<VertexBuffer> squareVertexBuffer(VertexBuffer::Create(vertices2, sizeof(vertices2)));

		squareVertexBuffer->SetLayout
		({
			{ ShaderDataType::Float3, "a_Position" }
		});
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		std::shared_ptr<IndexBuffer> squareIndexBuffer(IndexBuffer::Create(indices2, sizeof(indices2) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

		std::string vertexSource = 
		R"(
				#version 330 core

				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;

				out vec3 v_Position;
				out vec4 v_Color;

				void main()
				{
					v_Position = a_Position;
					v_Color = a_Color;

					gl_Position = vec4(a_Position, 1.0f);
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

		m_Shader.reset(new Shader(vertexSource, fragmentSource));

		std::string squareVertexSource =
			R"(
				#version 330 core

				layout(location = 0) in vec3 a_Position;
	
				out vec3 v_Position;
	
				void main()
				{
					v_Position = a_Position;

					gl_Position = vec4(a_Position, 1.0);
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

		m_SquareShader.reset(new Shader(squareVertexSource, squareFragmentSource));
	}

	Application::~Application() {}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);

			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			RenderCommand::SetClearColor(glm::vec4(0.1, 0.1, 0.1, 1.0));
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_SquareShader->Bind();
			Renderer::Submit(m_SquareVertexArray);

			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();

			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();

			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}