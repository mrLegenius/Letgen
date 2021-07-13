#include <Letgen.h>
#include <glm/glm.hpp>

class ExampleLayer : public Letgen::Layer
{
public:
	ExampleLayer() : Layer("Example") { }

	void OnUpdate() override
	{
		if(Letgen::Input::IsKeyPressed(KeyCode::Tab))
			Letgen::Log::Info("Cos of 2 = {0}", glm::cos(2));
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