#include "Sandbox2D.h"

#include "ImGui/imgui.h"
#include "Letgen/Debug/Instrumentor.h"

Sandbox2D::Sandbox2D() : Layer("Sandbox2D") { }

void Sandbox2D::OnAttach()
{
	LE_PROFILE_FUNCTION();
	
	m_Sprite = std::make_shared<Letgen::Sprite>("assets/textures/love.jpg");

    Letgen::FramebufferSpecification fbSpec;
    fbSpec.width = Letgen::Application::Get().GetWindow().GetWidth();
    fbSpec.height = Letgen::Application::Get().GetWindow().GetHeight();

    m_Framebuffer = Letgen::Framebuffer::Create(fbSpec);
}

void Sandbox2D::OnDetach()
{
	LE_PROFILE_FUNCTION();
	
}

void Sandbox2D::OnUpdate()
{
	LE_PROFILE_FUNCTION();

	m_CameraController.Update();

    Letgen::Renderer2D::ResetStats();

	{
        m_Framebuffer->Bind();
		LE_PROFILE_SCOPE("Renderer Begin");
		Letgen::Renderer2D::BeginScene(m_CameraController.GetCamera());
	}

	{
		static float rotation = 0;
		rotation += 45.0f * Letgen::Time::GetDeltaTime();

		LE_PROFILE_SCOPE("Renderer Draw");
		for (float i = -5.0f; i < 5.0f; i  += 0.5f)
			for (float j = -5.0f; j < 5.0f; j += 0.5f)
			{
				glm::vec4 c{ (i + 3.0f) / 6.0f, (i + 5.0f) / 10.0f, (i + 10.0f) / 15.0f, 1.0f };
				Letgen::Renderer2D::DrawQuad({
				{i, j},0.0f,{0.45f, 0.45f} },
				c);
			}
	}
	{
		LE_PROFILE_SCOPE("Renderer End");
		Letgen::Renderer2D::EndScene();
		m_Framebuffer->Unbind();
	}
}

void Sandbox2D::OnEvent(Letgen::Event& event)
{
	m_CameraController.OnEvent(event);
}

void Sandbox2D::OnImGuiRender()
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
	            Letgen::Application::Get().Close();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    
	ImGui::End();

    ImGui::Begin("Statistics");

    const auto stats = Letgen::Renderer2D::GetStats();

    ImGui::Text("Renderer2D Stats:");
    ImGui::Text("Draw Calls: %d", stats.drawCalls);
    ImGui::Text("Quads Count: %d", stats.quadCount);
    ImGui::Text("Vertices Count: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices Count: %d", stats.GetTotalIndexCount());
    uint32_t textureId = m_Framebuffer->GetColorAttachmentRendererID();
    ImGui::Image((void*)textureId, ImVec2(1280, 720));

    ImGui::End();

}

