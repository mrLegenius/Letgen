#include "pch.h"
#include "Scene.h"

#include "Component.h"
#include "Letgen/Renderer/Renderer2D.h"
#include "Letgen/Scene/Entity.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Letgen
{
	void Scene::OnUpdate()
	{
		
		// Update scripts
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
			{
				//TODO: Move to Scene::OnSceneStarted
				if (!nsc.instance)
				{
					nsc.instance = nsc.InstantiateScript();
					nsc.instance->m_Entity = Entity{ entity, this };
					nsc.instance->OnCreate();
				}

				nsc.instance->OnUpdate();
			});
		}
		
		Camera* mainCamera = nullptr;
		glm::mat4 cameraTransform;
		//Render Scene
		{
			auto group = m_Registry.group<TransformComponent>(entt::get<CameraComponent>);
			for (auto entity : group)
			{
				auto [transform, camera] = group.get<TransformComponent, CameraComponent>(entity);

				if (camera.isMain)
				{
					mainCamera = &camera.camera;
					cameraTransform = transform.GetModel();
					break;
				}
			}
		}
		
		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, cameraTransform);

			auto view = m_Registry.view<TransformComponent, SpriteRendererComponent>();
			for (auto entity : view)
			{
				auto [transform, sprite] = view.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawQuad(transform.GetModel(), sprite.color);
			}


			Renderer2D::EndScene();
		}
	}

	void Scene::OnViewportResized(const uint32_t width, const uint32_t height)
	{
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& camera = view.get<CameraComponent>(entity);

			if (camera.fixedAspectRatio) continue;

			camera.camera.SetViewportSize(width, height);
		}
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		auto entity = Entity(m_Registry.create(), this);
		entity.AddComponent<TransformComponent>();
		entity.AddComponent<TagComponent>(name);

		return entity;
	}
}
