#pragma once
#include "Letgen/Debug/Instrumentor.h"

#ifdef LE_PLATFORM_WINDOWS

extern Letgen::Application* Letgen::CreateApplication();

int main(int argc, char* argv[])
{
	Letgen::Log::Logger::Init();

	LE_PROFILE_BEGIN_SESSION("Startup", "LetgenProfile-Startup.json");
	auto app = Letgen::CreateApplication();
	LE_PROFILE_END_SESSION();

	LE_PROFILE_BEGIN_SESSION("Startup", "LetgenProfile-Runtime.json");
	app->Run();
	LE_PROFILE_END_SESSION();

	LE_PROFILE_BEGIN_SESSION("Startup", "LetgenProfile-Shutdown.json");
	delete app;
	LE_PROFILE_END_SESSION();
}

#endif