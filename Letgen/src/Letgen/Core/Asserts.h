#pragma once
#include "Letgen/Core/Logger.h"

#ifdef LE_DEBUG
#define LE_ENABLE_ASSERTS 1
#endif

#if LE_ENABLE_ASSERTS
	#define LE_ASSERT(x, ...) { if(!(x)) { Log::Error("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define LE_CORE_ASSERT(x, ...) { if(!(x)) { Log::CoreError("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define LE_ASSERT(x, ...)
	#define LE_CORE_ASSERT(x, ...)
#endif
