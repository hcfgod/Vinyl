#include "vlpch.h"

#include "Vinyl/Scene/Entity.h"

namespace Vinyl
{
	Entity::Entity(entt::entity handle, Scene* scene) : m_EntityHandle(handle), m_Scene(scene)
	{
	}
}