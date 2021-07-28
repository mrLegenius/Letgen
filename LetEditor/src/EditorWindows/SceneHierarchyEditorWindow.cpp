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

		if (entity.HasComponent<CameraComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(),
				ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
			{
				auto& cc = entity.GetComponent<CameraComponent>();

				ImGui::Checkbox("Main", &cc.isMain);
				ImGui::Checkbox("Fixed aspect ratio", &cc.fixedAspectRatio);
				const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
				const char* currentProjectionTypeString = projectionTypeStrings[static_cast<int>(cc.camera.GetProjectionType())];
				if(ImGui::BeginCombo("Projection", currentProjectionTypeString))
				{
					for (int i = 0; i < 2; i++)
					{
						const bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
						if(ImGui::Selectable(projectionTypeStrings[i], isSelected))
						{
							currentProjectionTypeString = projectionTypeStrings[i];
							cc.camera.SetProjectionType(static_cast<SceneCamera::ProjectionType>(i));
						}

						if(isSelected)
						{
							ImGui::SetItemDefaultFocus();
						}
					}
					
					ImGui::EndCombo();
				}

				if(cc.camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
				{
					float size = cc.camera.GetOrthographicSize();
					if(ImGui::DragFloat("Orthographic size", &size))
						cc.camera.SetOrthographicSize(size);

					float nearClip = cc.camera.GetOrthographicNear();
					if(ImGui::DragFloat("Near clip", &nearClip))
						cc.camera.SetOrthographicNear(nearClip);

					float farClip = cc.camera.GetOrthographicFar();
					if(ImGui::DragFloat("Far clip", &farClip))
						cc.camera.SetOrthographicFar(farClip);
				}
				else if (cc.camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
				{
					float fov = glm::degrees(cc.camera.GetFieldOfView());
					ImGui::DragFloat("Field of View", &fov);
					cc.camera.SetFieldOfView(glm::radians(fov));

					float nearClip = cc.camera.GetPerspectiveNear();
					ImGui::DragFloat("Near clip", &nearClip);
					cc.camera.SetPerspectiveNear(nearClip);

					float farClip = cc.camera.GetPerspectiveFar();
					ImGui::DragFloat("Far clip", &farClip);
					cc.camera.SetPerspectiveFar(farClip);
				}
				
				ImGui::TreePop();
			}
		}

		if (entity.HasComponent<SpriteRendererComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(SpriteRendererComponent).hash_code(),
				ImGuiTreeNodeFlags_DefaultOpen, "Sprite Renderer"))
			{
				auto& spriteRenderer = entity.GetComponent<SpriteRendererComponent>();

				ImGui::ColorEdit4("Color", value_ptr(spriteRenderer.color));

				char buffer[256];
				memset(buffer, 0, sizeof buffer);
				strcpy_s(buffer, sizeof buffer, spriteRenderer.texture.c_str());

				if (ImGui::InputText("Texture", buffer, sizeof buffer))
				{
					spriteRenderer.texture = std::string(buffer);
				}
				
				ImGui::TreePop();
			}
		}
	}
}
