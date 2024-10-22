#pragma once

#include "entt.hpp"
#include "Vinyl/Core/Timestep.h"

namespace Vinyl
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();
		Entity CreateEntity(const std::string& name = std::string());

		void OnViewportResize(uint32_t width, uint32_t height);
		void OnUpdate(TimeStep ts);
	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
		friend class Entity;
	};
}