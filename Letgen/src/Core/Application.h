#pragma once

#include "Core.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

#include "GUI/ImGuiLayer.h"

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
		Window& GetWindow() const { return *m_Window; }
	private:
		bool OnWindowClosed(WindowClosedEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_IsRunning = true;

		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		unsigned int m_VertexBuffer;
		unsigned int m_IndexBuffer;
		Shader* m_Shader;
		
		static Application* s_Instance;
	};

	Application* CreateApplication();
}
