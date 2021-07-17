#pragma once

#include "Core.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Window.h"
#include "Letgen/Events/ApplicationEvent.h"

#include "Timestep.h"

#include "Letgen/GUI/ImGuiLayer.h"

namespace Letgen
{
	class Shader;

	class LETGEN_API Application
	{
	public:
		
		Application();
		~Application();

		void OnEvent(Event& e);
		
		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		static Application& Get() { return *s_Instance; }
		[[nodiscard]] Window& GetWindow() const { return *m_Window; }
	private:
		bool OnWindowClosed(WindowClosedEvent& e);
		bool OnWindowResized(WindowResizedEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_IsRunning = true;
		LayerStack m_LayerStack;
		
		float m_LastFrameTime = 0.0f;
		bool m_Minimized = false;

		static Application* s_Instance;
	};

	Application* CreateApplication();
}
