#pragma once
#include <entt.hpp>
#include "Scene.h"
#include "Letgen/Core/Asserts.h"

namespace Letgen
{	
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity id, Scene* scene);

		~Entity() = default;

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.try_get<T>(m_EntityID);
		}

		template<typename T, typename ... Args>
		T& AddComponent(Args&& ... args)
		{
			LET_CORE_ASSERT(!HasComponent<T>(), "Entity already has this component!");

			return m_Scene->m_Registry.emplace<T>(m_EntityID, std::forward<Args>(args)...);
		}


		template<typename T>
		T& GetComponent()
		{
			LET_CORE_ASSERT(HasComponent<T>(), "Entity does not have this component!");

			return m_Scene->m_Registry.get<T>(m_EntityID);
		}

		template<typename T>
		void RemoveComponent()
		{
			LET_CORE_ASSERT(HasComponent<T>(), "Entity does not have this component!");

			return m_Scene->m_Registry.remove<T>(m_EntityID);
		}

		operator bool() const { return m_EntityID != entt::null; }
	private:
		entt::entity m_EntityID{ entt::null };
		Scene* m_Scene = nullptr;	
	};
}
