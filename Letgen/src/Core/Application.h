#pragma once

#include "Core.h"

namespace Letgen
{
	class LETGEN_API Application
	{
	public:
		Application();
		~Application();
		void Run();
	};

	Application* CreateApplication();
}