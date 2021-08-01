﻿#include "pch.h"
#include "EditorLayer.h"

#include <glm/gtc/matrix_transform.hpp>

#include "glm/gtc/type_ptr.hpp"
#include "ImGui/imgui.h"
#include "ImGuizmo/ImGuizmo.h"

#include "Letgen/Scene/SceneSerializer.h"
#include "Letgen/Utils/PlatformUtils.h"
#include "Letgen/Math/Math.h"

namespace Letgen
{
    EditorLayer::EditorLayer() : Layer("EditorLayer") { }

    void EditorLayer::OnAttach()
    {
        LET_PROFILE_FUNCTION();

        FramebufferSpecification fbSpec;
        fbSpec.width = Application::Get().GetWindow().GetWidth();
        fbSpec.height = Application::Get().GetWindow().GetHeight();

        m_Framebuffer = Framebuffer::Create(fbSpec);

        m_ActiveScene = CreateRef<Scene>();

        /*m_SquareEntity = m_ActiveScene->CreateEntity("Square");
        m_SquareEntity.AddComponent<SpriteRendererComponent>(glm::vec4(1.0f, 0.3f, 0.2f, 1.0f));

        m_CameraEntity = m_ActiveScene->CreateEntity("Camera");
        m_CameraEntity.AddComponent<CameraComponent>();
    	
        class CameraController : public ScriptableEntity
        {
        public:
            void OnUpdate() override
            {
                auto& translation = GetComponent<TransformComponent>().position;

                const float speed = 5.0f;
                const float dt = Time::GetDeltaTime();

                if (Input::IsKeyDown(KeyCode::A))
                    translation.x -= speed * dt;
                if (Input::IsKeyDown(KeyCode::D))
                    translation.x += speed * dt;
                if (Input::IsKeyDown(KeyCode::W))
                    translation.y += speed * dt;
                if (Input::IsKeyDown(KeyCode::S))
                    translation.y -= speed * dt;
            }
        };

        m_CameraEntity.AddScript<CameraController>();*/

        m_Hierarchy.SetContext(m_ActiveScene);

        SceneSerializer sceneSerializer(m_ActiveScene);
        sceneSerializer.Deserialize("assets/scenes/FirstScene.letscene");
    }

    void EditorLayer::OnDetach()
    {
        LET_PROFILE_FUNCTION();

    }

    void EditorLayer::OnUpdate()
    {
        const auto width = static_cast<uint32_t>(m_ViewportSize.x);
        const auto height = static_cast<uint32_t>(m_ViewportSize.y);

        Renderer2D::ResetStats();
    	
        if(const FramebufferSpecification spec = m_Framebuffer->GetSpecification();
            m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f &&
            (spec.width != width || spec.height != height))
        {
            m_Framebuffer->Resize(width, height);
            m_ActiveScene->OnViewportResized(width, height);
        }
    	
        LET_PROFILE_FUNCTION();
        if (m_ViewportFocused)
            m_CameraController.Update();

        m_Framebuffer->Bind();
        m_ActiveScene->OnUpdate();

        //COOL GRADIENT COLOR
        //glm::vec4 c{ (i + 3.0f) / 6.0f, (i + 5.0f) / 10.0f, (i + 10.0f) / 15.0f, 1.0f };
        m_Framebuffer->Unbind();
    }

    void EditorLayer::OnEvent(Event& event)
    {
		m_CameraController.OnEvent(event);

        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<KeyPressedEvent>(LET_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
    }

    void EditorLayer::OnImGuiRender()
    {
        LET_PROFILE_FUNCTION();

        DrawDockSpace();
        DrawViewport();	
        DrawStatistics();
        m_Hierarchy.OnImGuiRender();
    }

    bool EditorLayer::OnKeyPressed(KeyPressedEvent& event)
    {
    	//Shortcuts
        if (event.GetRepeatCount() > 0)
            return false;

        const bool control = Input::IsKeyDown(KeyCode::LeftControl) ||
            Input::IsKeyDown(KeyCode::RightControl);
        const bool shift = Input::IsKeyDown(KeyCode::LeftShift) ||
            Input::IsKeyDown(KeyCode::RightShift);
        const bool alt = Input::IsKeyDown(KeyCode::LeftAlt) ||
            Input::IsKeyDown(KeyCode::RightAlt);

	    switch ((KeyCode)event.GetKeyCode())
	    {
        
        case KeyCode::N:
        {
            if (control) { CreateNewScene(); }
            break;
        }
        case KeyCode::O:
        {
            if (control) { OpenScene(); }
            break;
        }
        case KeyCode::S:
        {
            if (control && shift) { SaveSceneAs(); }
            break;
        }
        case KeyCode::Q:
        {
            m_GizmoType = -1;
            break;
        }
        case KeyCode::W:
        {
            m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
            break;
        }
        case KeyCode::E:
        {
            m_GizmoType = ImGuizmo::OPERATION::ROTATE;
            break;
        }
        case KeyCode::R:
        {
            m_GizmoType = ImGuizmo::OPERATION::SCALE;
            break;
        } 
	    	
	    default:
            break;
	    }
    }

    void EditorLayer::CreateNewScene()
    {
        m_ActiveScene = CreateRef<Scene>();
        m_ActiveScene->OnViewportResized(
            static_cast<uint32_t>(m_ViewportSize.x),
            static_cast<uint32_t>(m_ViewportSize.y));
        m_Hierarchy.SetContext(m_ActiveScene);
    }

    void EditorLayer::OpenScene()
    {
        const auto filepath = FileDialogs::OpenFile("Letgen Scene (*.letscene)\0*.letscene\0");
        if (!filepath.empty())
        {
            m_ActiveScene = CreateRef<Scene>();
            m_ActiveScene->OnViewportResized(
                static_cast<uint32_t>(m_ViewportSize.x),
                static_cast<uint32_t>(m_ViewportSize.y));
            m_Hierarchy.SetContext(m_ActiveScene);

            SceneSerializer sceneSerializer(m_ActiveScene);
            sceneSerializer.Deserialize(filepath);
        }
    }

    void EditorLayer::SaveSceneAs()
    {
        const auto filepath = FileDialogs::OpenFile("Letgen Scene (*.letscene)\0*.letscene\0");
        if (!filepath.empty())
        {
            SceneSerializer sceneSerializer(m_ActiveScene);
            sceneSerializer.Serialize(filepath);
        }
    }

    void EditorLayer::DrawViewport()
    {
        LET_PROFILE_FUNCTION();
    	
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("Viewport");

        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();
        Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused && !m_ViewportHovered);
    	
        const ImVec2 viewportSize = ImGui::GetContentRegionAvail();

        m_ViewportSize = { viewportSize.x, viewportSize.y };

        const uint32_t textureId =
            m_Framebuffer->GetColorAttachmentRendererID();

        ImGui::Image(
            (void*)textureId,
            ImVec2(m_ViewportSize.x, m_ViewportSize.y),
            ImVec2(0, 1),
            ImVec2(1, 0)
        );

        const bool snap = Input::IsKeyDown(KeyCode::LeftControl);
        const float snapValue = m_GizmoType == ImGuizmo::OPERATION::ROTATE ? 5.0f : 0.5f;
    	
    	//Gizmos
        Entity selectedEntity = m_Hierarchy.GetSelectedEntity();
    	if (selectedEntity && m_GizmoType != -1)
    	{
            ImGuizmo::SetOrthographic(false);
            ImGuizmo::SetDrawlist();
            const auto windowPos = ImGui::GetWindowPos();
            const auto windowSize = ImGui::GetWindowSize();
    		
            ImGuizmo::SetRect(windowPos.x, windowPos.y, windowSize.x, windowSize.y);

    		//Camera
            auto cameraEntity = m_ActiveScene->GetMainCameraEntity();
            const auto& camera = cameraEntity.GetComponent<CameraComponent>().camera;
            glm::mat4 cameraView = glm::inverse(cameraEntity.GetComponent<TransformComponent>().GetModel());
            const glm::mat4& cameraProjection = camera.GetProjection();

            float snapValues[3] = { snapValue, snapValue, snapValue };
    		//Entity transform
            auto& tc = selectedEntity.GetComponent<TransformComponent>();
            glm::mat4 model = tc.GetModel();
    		
            ImGuizmo::Manipulate(glm::value_ptr(cameraView),
                glm::value_ptr(cameraProjection),
                static_cast<ImGuizmo::OPERATION>(m_GizmoType),
                ImGuizmo::LOCAL,
                glm::value_ptr(model),
                nullptr,
                snap ? snapValues : nullptr);

    		if(ImGuizmo::IsUsing())
    		{
                glm::vec3 position, rotation, scale;
                Math::DecomposeTransform(model, position, rotation, scale);
    			
                tc.position = position;
    			
                //Adding delta rotation to avoid Gimbal lock
                tc.rotation += rotation - tc.rotation;

                tc.scale = scale;
    		}
    	}
    	
        ImGui::End();
        ImGui::PopStyleVar();
    }

    void EditorLayer::DrawStatistics()
    {
        LET_PROFILE_FUNCTION();
    	
        ImGui::Begin("Statistics");

        const auto stats = Renderer2D::GetStats();

        ImGui::Text("Renderer2D Stats:");
        ImGui::Text("Draw Calls: %d", stats.drawCalls);
        ImGui::Text("Quads Count: %d", stats.quadCount);
        ImGui::Text("Vertices Count: %d", stats.GetTotalVertexCount());
        ImGui::Text("Indices Count: %d", stats.GetTotalIndexCount());

        ImGui::End();
    }

    void EditorLayer::DrawDockSpace()
    {
        LET_PROFILE_FUNCTION();
    	
        static bool open = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &open, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        ImGuiStyle& style = ImGui::GetStyle();
        float minWinSizeX = style.WindowMinSize.x;
        style.WindowMinSize.x = 400.0f;
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        style.WindowMinSize.x = minWinSizeX;

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New Scene", "Ctrl+N"))
                {
                    CreateNewScene();
                }

                if (ImGui::MenuItem("Open Scene...", "Ctrl+O"))
                {
                    OpenScene();
                }
            	
                if(ImGui::MenuItem("Save Scene As...", "Ctrl+Shift+S"))
                {
                    SaveSceneAs();
                }
            	
                if (ImGui::MenuItem("Exit")) Application::Get().Close();

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ImGui::End();
    }
}
