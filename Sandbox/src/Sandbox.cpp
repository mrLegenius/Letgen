#include <Letgen.h>

class ExampleLayer : public Letgen::Layer
{
public:
	ExampleLayer() : Layer("Example") { }

	void OnUpdate() override
	{
		Letgen::Log::Info("ExampleLayer::OnUpdate");
	}

	void OnEvent(Event& event) override
	{
		Letgen::Log::Trace("{0}", event);
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