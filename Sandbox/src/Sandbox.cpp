#include <Letgen.h>


class Sandbox : public Letgen::Application
{
public:
	Sandbox() { }
	~Sandbox() { }
};

Letgen::Application* Letgen::CreateApplication()
{
	Log::Info("No shit man");
	return new Sandbox;
}