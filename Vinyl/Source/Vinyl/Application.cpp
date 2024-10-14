#include "vlpch.h"
#include "Application.h"

#include "Input.h"

#include <Glad/glad.h>

namespace Vinyl
{
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Vinyl::ShaderDataType::Bool:      return GL_BOOL;
			case Vinyl::ShaderDataType::Int:       return GL_INT;
			case Vinyl::ShaderDataType::Int2:      return GL_INT;
			case Vinyl::ShaderDataType::Int3:      return GL_INT;
			case Vinyl::ShaderDataType::Int4:      return GL_INT;
			case Vinyl::ShaderDataType::Float:     return GL_FLOAT;
			case Vinyl::ShaderDataType::Float2:    return GL_FLOAT;
			case Vinyl::ShaderDataType::Float3:    return GL_FLOAT;
			case Vinyl::ShaderDataType::Float4:    return GL_FLOAT;
			case Vinyl::ShaderDataType::Mat3:      return GL_FLOAT;
			case Vinyl::ShaderDataType::Mat4:      return GL_FLOAT;
		}

		VL_CORE_ASSERT(false, "Unknown ShaderDataType.");
		return 0;
	}

	Application::Application()
	{
		VL_CORE_ASSERT(!s_Instance, "Application already exist.");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_ImGuiLayer = new ImGuiLayer();

		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, -0.0f, 0.2f, 0.4f, 1.0f, 1.0f,
			 0.5f, -0.5f, -0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, -0.0f, 0.5f, 0.3f, 1.0f, 1.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			BufferLayout layout
			{
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float4, "a_Color" },
			};
			m_VertexBuffer->SetLayout(layout);
		}

		const auto& layout = m_VertexBuffer->GetLayout();
		uint32_t index = 0;
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), reinterpret_cast<void*>(static_cast<uintptr_t>(element.Offset)));
			index++;
		}

		uint32_t indices[3] =
		{
			0, 1, 2,
		};

		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

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
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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