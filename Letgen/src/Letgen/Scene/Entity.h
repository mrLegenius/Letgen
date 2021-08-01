﻿#pragma once
#include <entt.hpp>

#include "Scene.h"
#include "Letgen/Core/Asserts.h"

namespace Letgen
{
	struct NativeScriptComponent;
	
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity id, Scene* scene);

		~Entity() = default;

		template<typename T>
		bool HasComponent()
		{
			LET_CORE_ASSERT(m_Scene->m_Registry.valid(m_EntityID), "Entity is not valid!");
			return m_Scene->m_Registry.any_of<T>(m_EntityID);
		}

		template<typename T, typename ... Args>
		T& AddComponent(Args&& ... args)
		{	
			LET_CORE_ASSERT(m_Scene->m_Registry.valid(m_EntityID), "Entity is not valid!");
			LET_CORE_ASSERT(!HasComponent<T>(), "Entity already has this component!");

			T& component = m_Scene->m_Registry.emplace<T>(m_EntityID, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded(*this, component);
			
			return component;
		}


		template<typename T>
		T& GetComponent()
		{
			LET_CORE_ASSERT(m_Scene->m_Registry.valid(m_EntityID), "Entity is not valid!");
			LET_CORE_ASSERT(HasComponent<T>(), "Entity does not have this component!");

			return m_Scene->m_Registry.get<T>(m_EntityID);
		}

		template<typename T>
		void RemoveComponent()
		{
			LET_CORE_ASSERT(m_Scene->m_Registry.valid(m_EntityID), "Entity is not valid!");
			LET_CORE_ASSERT(HasComponent<T>(), "Entity does not have this component!");

			return m_Scene->m_Registry.remove<T>(m_EntityID);
		}

		template <typename T>
		void AddScript()
		{
			LET_CORE_ASSERT(m_Scene->m_Registry.valid(m_EntityID), "Entity is not valid!");
			LET_CORE_ASSERT(!HasComponent<T>(), "Entity already has this component!");

			return AddComponent<NativeScriptComponent>().Bind<T>();
		}

		operator bool() const { return m_EntityID != entt::null; }
		operator uint32_t() const { return static_cast<uint32_t>(m_EntityID); }
		operator entt::entity() const { return m_EntityID; }

		bool operator ==(const Entity& other) const
		{
			return m_EntityID == other.m_EntityID &&
				m_Scene == other.m_Scene;
		}
		bool operator !=(const Entity& other) const
		{
			return !(*this == other);
		}
	private:
		entt::entity m_EntityID{ entt::null };
		Scene* m_Scene = nullptr;	
	};
}
