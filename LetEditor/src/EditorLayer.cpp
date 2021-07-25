#include "pch.h"
#include "EditorLayer.h"

#include "ImGui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>

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

        m_SquareEntity = m_ActiveScene->CreateEntity("Square");
        m_SquareEntity.AddComponent<Transform2DComponent>();
        m_SquareEntity.AddComponent<SpriteComponent>(glm::vec4(1.0f, 0.3f, 0.2f, 1.0f));

        m_CameraEntity = m_ActiveScene->CreateEntity("Camera");
        m_CameraEntity.AddComponent<CameraComponent>();
    	
        class CameraController : public ScriptableEntity
        {
        public:
            void OnUpdate() override
            {
                auto& translation = GetComponent<TransformComponent>().transform;

                const float speed = 5.0f;
                const float dt = Time::GetDeltaTime();

                if (Input::IsKeyPressed(KeyCode::A))
                    translation[3][0] -= speed * dt;
                if (Input::IsKeyPressed(KeyCode::D))
                    translation[3][0] += speed * dt;
                if (Input::IsKeyPressed(KeyCode::W))
                    translation[3][1] += speed * dt;
                if (Input::IsKeyPressed(KeyCode::S))
                    translation[3][1] -= speed * dt;
            }
        };

        m_CameraEntity.AddScript<CameraController>();
    	
    	
       
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
    }

    void EditorLayer::OnImGuiRender()
    {
        LET_PROFILE_FUNCTION();

        DrawDockSpace();
        DrawViewport();	
        DrawStatistics();
    }

    void EditorLayer::DrawViewport()
    {
        LET_PROFILE_FUNCTION();
    	
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("Viewport");

        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();
        Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);
    	
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
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &open, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit"))
                {
                    Application::Get().Close();
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ImGui::End();
    }
}
