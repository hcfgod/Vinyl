#include "vlpch.h"

#include "Shader.h"
#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Vinyl
{
	// Shader Implementation
	Ref<Shader> Shader::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: VL_CORE_ASSERT(false, "Currently we do not support RendererAPI::None. Please choose a different Rendering API."); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(filePath);
		}

		VL_CORE_ASSERT(false, "Unknown rendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: VL_CORE_ASSERT(false, "Currently we do not support RendererAPI::None. Please choose a different Rendering API."); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(name, vertexSource, fragmentSource);
		}

		VL_CORE_ASSERT(false, "Unknown rendererAPI!");
		return nullptr;
	}


	// Shader Library Implementation
	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		VL_CORE_ASSERT(!Exists(name), "{0} shader already exist", name);
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		VL_CORE_ASSERT(Exists(name), "{0} shader does not exist", name);
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}