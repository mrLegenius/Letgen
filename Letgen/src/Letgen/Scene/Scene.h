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
		void DestroyEntity(Entity entity);
		
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth;
		uint32_t m_ViewportHeight;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyEditorWindow;
	};
}
