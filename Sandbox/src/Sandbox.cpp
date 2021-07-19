#include <Letgen.h>
#include <Letgen/Core/EntryPoint.h>

#include "Sandbox2D.h"

class Sandbox : public Letgen::Application
{
public:
	Sandbox() : Application("Sandbox")
	{
		PushLayer(new Sandbox2D);
	}
	~Sandbox() = default;
};

Letgen::Application* Letgen::CreateApplication()
{
	return new Sandbox;
}