#pragma once

#include <string>

namespace Vinyl
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		~Shader();

		void Bind();
		void UnBind();
	private:
		uint32_t m_RendererID;
	};
}