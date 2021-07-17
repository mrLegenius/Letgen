#pragma once
#include "Timestep.h"

namespace Letgen
{
	class Application;

	class Time
	{
		friend Application;
	public:
		static Timestep GetDeltaTime();
	private:
		static Timestep s_DeltaTime;
	};
}
