#include "SceneHierarchyEditorWindow.h"

#include "glm/gtc/type_ptr.hpp"
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



	void SceneHierarchyEditorWindow::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		m_Context->m_Registry.each([&](auto entityID)
			{
				const Entity entity{ entityID, m_Context.get() };
				DrawEntityNode(entity);
			});

		if (ImGui::IsWindowHovered() && ImGui::IsMouseDown(0))
			m_SelectionContext = {};

		ImGui::End();

		ImGui::Begin("Properties");

		if (m_SelectionContext)
			DrawComponents(m_SelectionContext);

		ImGui::End();
	}

	void SceneHierarchyEditorWindow::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().tag;

		const auto flags =
			(m_SelectionContext == entity ? ImGuiTreeNodeFlags_Selected : 0) |
			ImGuiTreeNodeFlags_OpenOnArrow;

		const bool opened = ImGui::TreeNodeEx((void*)static_cast<uint32_t>(entity), flags, tag.c_str());

		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		if (!opened) return;

		ImGui::TreePop();
	}

	void SceneHierarchyEditorWindow::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().tag;

			char buffer[256];
			memset(buffer, 0, sizeof buffer);
			strcpy_s(buffer, sizeof buffer, tag.c_str());

			if (ImGui::InputText("Tag", buffer, sizeof buffer))
			{
				tag = std::string(buffer);
			}
		}

		if (entity.HasComponent<TransformComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(),
				ImGuiTreeNodeFlags_DefaultOpen,"Transform"))
			{
				auto& transform = entity.GetComponent<TransformComponent>().transform;
				ImGui::DragFloat3("Position", value_ptr(transform[3]), 0.5f);

				ImGui::TreePop();
			}
		}

		if (entity.HasComponent<TransformComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(),
				ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
			{
				auto& camera = entity.GetComponent<CameraComponent>();

				

				ImGui::TreePop();
			}
		}
	}
}
