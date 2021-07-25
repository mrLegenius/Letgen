#pragma once
#include "Letgen/Debug/Instrumentor.h"

#ifdef LET_PLATFORM_WINDOWS

extern Letgen::Application* Letgen::CreateApplication();

int main(int argc, char* argv[])
{
	Letgen::Log::Logger::Init();

	LET_PROFILE_BEGIN_SESSION("Startup", "LetgenProfile-Startup.json");
	auto app = Letgen::CreateApplication();
	LET_PROFILE_END_SESSION();

	LET_PROFILE_BEGIN_SESSION("Startup", "LetgenProfile-Runtime.json");
	app->Run();
	LET_PROFILE_END_SESSION();

	LET_PROFILE_BEGIN_SESSION("Startup", "LetgenProfile-Shutdown.json");
	delete app;
	LET_PROFILE_END_SESSION();
}

#endif