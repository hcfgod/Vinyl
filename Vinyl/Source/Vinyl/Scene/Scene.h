#pragma once

#include "entt.hpp"
#include "Vinyl/Core/Timestep.h"

namespace Vinyl
{
	class Scene
	{
	public:
		Scene();
		~Scene();
		entt::entity CreateEntity();

		entt::registry& Reg() { return m_Registry; }
		void OnUpdate(TimeStep ts);
	private:
		entt::registry m_Registry;
	};
}