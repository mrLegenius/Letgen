#pragma once

#include "Core.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

namespace Letgen
{
	class LETGEN_API Application
	{
	public:
		Application();
		~Application();

		void OnEvent(Event& e);
		
		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;

		bool m_IsRunning = true;

		LayerStack m_LayerStack;
	};

	Application* CreateApplication();
}
