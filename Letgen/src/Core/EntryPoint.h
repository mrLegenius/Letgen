#pragma once

#ifdef LE_PLATFORM_WINDOWS

extern Letgen::Application* Letgen::CreateApplication();

int main(int argc, char* argv[])
{
	Letgen::Log::Logger::Init();
	
	auto app = Letgen::CreateApplication();
	app->Run();
	delete app;
}

#endif