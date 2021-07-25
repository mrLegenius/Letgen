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

		void OnViewportResized(uint32_t width, uint32_t height);
		
		Entity CreateEntity(const std::string& name = "Entity");
	private:
		entt::registry m_Registry;

		friend class Entity;
	};
}