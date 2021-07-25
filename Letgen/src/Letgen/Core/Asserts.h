#pragma once
#include "Letgen/Core/Logger.h"

#ifdef LET_DEBUG
#define LET_ENABLE_ASSERTS 1
#endif

#if LET_ENABLE_ASSERTS
	#define LET_ASSERT(x, ...) { if(!(x)) { Log::Error("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define LET_CORE_ASSERT(x, ...) { if(!(x)) { Log::CoreError("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define LET_ASSERT(x, ...)
	#define LET_CORE_ASSERT(x, ...)
#endif
