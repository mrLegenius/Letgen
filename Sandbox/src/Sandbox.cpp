#include <Letgen.h>

class ExampleLayer : public Letgen::Layer
{
public:
	ExampleLayer() : Layer("Example") { }

	void OnUpdate() override
	{
		if(Letgen::Input::IsKeyPressed(KeyCode::Tab))
			Letgen::Log::Info("Tab is pressed!!");
	}

	void OnEvent(Event& event) override
	{
	}
};


class Sandbox : public Letgen::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer);
		PushOverlay(new Letgen::ImGuiLayer);
	}
	~Sandbox() { }
};

Letgen::Application* Letgen::CreateApplication()
{
	return new Sandbox;
}