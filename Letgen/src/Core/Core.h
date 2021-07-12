#pragma once

#ifdef LE_PLATFORM_WINDOWS
	#ifdef LE_BUILD_DLL
		#define LETGEN_API __declspec(dllexport)
	#else
		#define LETGEN_API __declspec(dllimport)
	#endif
#else
	#error Only supports Windows so far!
#endif

#ifdef LE_ENABLE_ASSERTS
	#define LE_ASSERT(x, ...) { if(!(x)) { Log::Error("Assertion Failed {0}", __VA_ARGS__); __debugbreak(); } }
	#define LE_INNER_ASSERT(x, ...) { if(!(x)) { Log::InnerError("Assertion Failed {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define LE_ASSERT(x, ...)
	#define LE_INNER_ASSERT(x, ...)
#endif


constexpr int Bit(const int offset) { return 1 << offset; }
