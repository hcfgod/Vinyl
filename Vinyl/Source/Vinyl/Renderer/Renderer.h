#pragma once

namespace Vinyl
{
	enum class RendererAPI
	{
		None = 0, OpenGL = 1
	};

	class Renderer
	{
	public:
		static inline RendererAPI GetAPI() { return s_RendererAPI; }
		static inline void SetAPI(RendererAPI renderAPI) { s_RendererAPI = renderAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};
}