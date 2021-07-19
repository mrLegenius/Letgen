#include "pch.h"
#include "EditorLayer.h"

#include "ImGui/imgui.h"

namespace Letgen
{
    EditorLayer::EditorLayer() : Layer("EditorLayer") { }

    void EditorLayer::OnAttach()
    {
        LE_PROFILE_FUNCTION();

        FramebufferSpecification fbSpec;
        fbSpec.width = Application::Get().GetWindow().GetWidth();
        fbSpec.height = Application::Get().GetWindow().GetHeight();

        m_Framebuffer = Framebuffer::Create(fbSpec);
    }

    void EditorLayer::OnDetach()
    {
        LE_PROFILE_FUNCTION();

    }

    void EditorLayer::OnUpdate()
    {
        LE_PROFILE_FUNCTION();

        m_CameraController.Update();

        Renderer2D::ResetStats();

        {
            m_Framebuffer->Bind();
            LE_PROFILE_SCOPE("Renderer Begin");
            Renderer2D::BeginScene(m_CameraController.GetCamera());
        }

        {
            static float rotation = 0;
            rotation += 45.0f * Time::GetDeltaTime();

            LE_PROFILE_SCOPE("Renderer Draw");
            for (float i = -5.0f; i < 5.0f; i += 0.5f)
                for (float j = -5.0f; j < 5.0f; j += 0.5f)
                {
                    glm::vec4 c{ (i + 3.0f) / 6.0f, (i + 5.0f) / 10.0f, (i + 10.0f) / 15.0f, 1.0f };
                    Renderer2D::DrawQuad({
                                             {i, j},0.0f,{0.45f, 0.45f} },
                                             c);
                }
        }
        {
            LE_PROFILE_SCOPE("Renderer End");
            Renderer2D::EndScene();
            m_Framebuffer->Unbind();
        }
    }

    void EditorLayer::OnEvent(Event& event)
    {
        m_CameraController.OnEvent(event);
    }

    void EditorLayer::OnImGuiRender()
    {
        LE_PROFILE_FUNCTION();

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

        DrawViewport();
    	
        ImGui::Begin("Statistics");

        const auto stats = Renderer2D::GetStats();

        ImGui::Text("Renderer2D Stats:");
        ImGui::Text("Draw Calls: %d", stats.drawCalls);
        ImGui::Text("Quads Count: %d", stats.quadCount);
        ImGui::Text("Vertices Count: %d", stats.GetTotalVertexCount());
        ImGui::Text("Indices Count: %d", stats.GetTotalIndexCount());

        ImGui::End();

    }

    void EditorLayer::DrawViewport()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("Viewport");

        const ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        if (m_ViewportSize != *((glm::vec2*)(&viewportSize)))
        {
            m_Framebuffer->Resize(static_cast<uint32_t>(viewportSize.x), static_cast<uint32_t>(viewportSize.y));
            m_ViewportSize = { viewportSize.x, viewportSize.y };

            m_CameraController.SetAspectRatio(viewportSize.x / viewportSize.y);
        }

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
}
