#include "pch.h"
#include "Scene.h"

#include "Component.h"
#include "Letgen/Scene/Entity.h"

namespace Letgen
{
	void Scene::OnUpdate()
	{
		
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		auto id = m_Registry.create();
		auto entity = Entity(id, this);
		entity.AddComponent<TransformComponent>();
		entity.AddComponent<TagComponent>(name);

		return entity;
	}
}
