#include "pch.h"
#include "ImGuiLayer.h"
#include "imgui.h"
#include "Letgen/Core/Application.h"

#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

//TEMP
#include <GLFW/glfw3.h>
namespace Letgen
{

	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
	{
		
	}

	void ImGuiLayer::OnAttach()
	{
		LE_PROFILE_FUNCTION();
		
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		auto& app = Application::Get();
		const auto window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		if(m_IsBlockingEvents)
		{
			ImGuiIO& io = ImGui::GetIO();
			event.handled |= event.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
			event.handled |= event.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
		}
	}
	void ImGuiLayer::OnDetach()
	{
		LE_PROFILE_FUNCTION();
		
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnImGuiRender()
	{
	}

	void ImGuiLayer::Begin()
	{
		LE_PROFILE_FUNCTION();
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		LE_PROFILE_FUNCTION();
		
		ImGuiIO& io = ImGui::GetIO();
		auto& app = Application::Get();
		auto& window = app.GetWindow();
		io.DisplaySize = ImVec2(static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()));

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::BlockEvents(const bool value)
	{
		m_IsBlockingEvents = value;
	}
}
