#pragma once
#include "Letgen.h"

namespace Letgen
{
	class SceneHierarchyEditorWindow
	{
	public:
		SceneHierarchyEditorWindow() = default;
		SceneHierarchyEditorWindow(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);

		void OnImGuiRender();
	private:
		Ref<Scene> m_Context = nullptr;
		Entity m_SelectionContext;

		friend class Scene;
	};
}
