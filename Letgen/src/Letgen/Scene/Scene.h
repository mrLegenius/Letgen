#pragma once
#include "entt.hpp"
namespace Letgen
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		void OnUpdate();
		entt::entity CreateEntity();
	private:
		entt::registry m_Registry;
	};
}