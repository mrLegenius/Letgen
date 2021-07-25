#pragma once
#include <entt.hpp>

namespace Letgen
{
	class Entity;
	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;

		void OnUpdate();

		Entity CreateEntity(const std::string& name = "Entity");
	private:
		entt::registry m_Registry;

		friend class Entity;
	};
}