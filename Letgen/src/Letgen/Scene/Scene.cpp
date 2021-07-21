#include "pch.h"
#include "Scene.h"

#include "Component.h"
#include "glm/glm.hpp"
namespace Letgen
{

	static void DoMath(const glm::mat4& transform)
	{
		
	}
	Scene::Scene()
	{
		struct MeshComponent
		{
			float value;
			MeshComponent() = default;
		};
		
		
		TransformComponent transform;
		
		entt::entity entity = m_Registry.create();
		DoMath(transform);
		auto& t = m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

		m_Registry.remove<TransformComponent>(entity);

		auto& t2 = m_Registry.get<TransformComponent>(entity);

		auto view = m_Registry.view<TransformComponent>();

		for (auto entity : view)
		{
			auto& t3 = view.get<TransformComponent>(entity);
		}

		auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);

		for (auto entity : group)
		{
			auto& [tr, ms] = group.get<TransformComponent, MeshComponent>(entity);
		
		}
	}

	Scene::~Scene()
	{
		
	}

	void Scene::OnUpdate()
	{
		
	}

	entt::entity Scene::CreateEntity()
	{
		return m_Registry.create();
	}
}
