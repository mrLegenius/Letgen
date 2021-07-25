#include "SceneHierarchyEditorWindow.h"

#include "ImGui/imgui.h"

namespace Letgen
{
	SceneHierarchyEditorWindow::SceneHierarchyEditorWindow(const Ref<Scene>& scene)
	{
		SetContext(scene);
	}

	void SceneHierarchyEditorWindow::SetContext(const Ref<Scene>& scene)
	{
		m_Context = scene;
	}

	void SceneHierarchyEditorWindow::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().tag;

		const auto flags = 
			(m_SelectionContext == entity ? ImGuiTreeNodeFlags_Selected : 0) |
			ImGuiTreeNodeFlags_OpenOnArrow;
		
		const bool opened = ImGui::TreeNodeEx((void*)static_cast<uint32_t>(entity), flags, tag.c_str());

		if(ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		if (!opened) return;

		ImGui::TreePop();
	}

	void SceneHierarchyEditorWindow::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		m_Context->m_Registry.each([&](auto entityID)
			{
				const Entity entity{ entityID, m_Context.get() };
				DrawEntityNode(entity);
			});
		
		ImGui::End();
	}
}
