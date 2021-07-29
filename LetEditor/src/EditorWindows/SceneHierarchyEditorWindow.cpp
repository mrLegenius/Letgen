#include "SceneHierarchyEditorWindow.h"

#include "glm/gtc/type_ptr.hpp"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"

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

		//Right click on a blank space
		if (ImGui::BeginPopupContextWindow(nullptr, 1, false))
		{
			if (ImGui::MenuItem("Create New Entity"))
				m_Context->CreateEntity("New Entity");

			ImGui::EndPopup();
		}
		
		ImGui::End();

		ImGui::Begin("Properties");

		if (m_SelectionContext)
		{
			DrawComponents(m_SelectionContext);

			if (ImGui::Button("Add Component"))
				ImGui::OpenPopup("AddComponent");

			if(ImGui::BeginPopup("AddComponent"))
			{
				if(ImGui::MenuItem("Camera"))
				{
					m_SelectionContext.AddComponent<CameraComponent>();
					ImGui::CloseCurrentPopup();
				}

				if (ImGui::MenuItem("Sprite Renderer"))
				{
					m_SelectionContext.AddComponent<SpriteRendererComponent>();
					ImGui::CloseCurrentPopup();
				}
				
				ImGui::EndPopup();
			}
		}
			

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

		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
				entityDeleted = true;

			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGui::TreePop();
		}

		if (entityDeleted)
		{
			m_Context->DestroyEntity(entity);
			if (m_SelectionContext == entity)
				m_SelectionContext = { };
		}

	}

	static void DrawVector3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		// -- Init -------------------------------------------------------
		ImGui::PushID(label.c_str());
		
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		const float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		const ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };
	
		// -- X Component ------------------------------------------------
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));

		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		
		ImGui::PopStyleColor(3);
		
		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		// -- Y Component ------------------------------------------------
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));

		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;

		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		// -- Z Component ------------------------------------------------
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));

		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;

		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f);
		ImGui::PopItemWidth();

		// -- Reset ------------------------------------------------------
		ImGui::PopStyleVar();
		ImGui::Columns();
		ImGui::PopID();
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

		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen
			| ImGuiTreeNodeFlags_AllowItemOverlap;
		
		if (entity.HasComponent<TransformComponent>())
		{
			const bool opened = ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(),
				treeNodeFlags, "Transform");
			
			if (opened)
			{
				auto& transform = entity.GetComponent<TransformComponent>();
				DrawVector3Control("Position", transform.position);

				glm::vec3 rotation = glm::degrees(transform.rotation);
				DrawVector3Control("Rotation", rotation);
				transform.rotation = glm::radians(rotation);
				
				DrawVector3Control("Scale", transform.scale, 1.0f);

				ImGui::TreePop();
			}
		}

		if (entity.HasComponent<CameraComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(),
				treeNodeFlags, "Camera"))
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
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			
			const bool opened = ImGui::TreeNodeEx((void*)typeid(SpriteRendererComponent).hash_code(),
				treeNodeFlags, "Sprite Renderer");
			
			ImGui::SameLine(ImGui::GetWindowWidth() - 45.0f);

			if (ImGui::Button("...", ImVec2{25.0f, 20.0f}))
			{
				ImGui::OpenPopup("ComponentSettings");
			}
			ImGui::PopStyleVar();

			bool removeComponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove component"))
				{
					removeComponent = true;
					ImGui::CloseCurrentPopup();
				}


				ImGui::EndPopup();
			}
			
			if (opened)
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

			if (removeComponent)
				entity.RemoveComponent<TransformComponent>();
		}
	}
}
