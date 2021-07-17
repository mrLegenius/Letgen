#include "pch.h"
#include "Time.h"

namespace Letgen
{
	Timestep Time::s_DeltaTime = 0;
	
	Timestep Time::GetDeltaTime()
	{
		return s_DeltaTime;
	}
}
