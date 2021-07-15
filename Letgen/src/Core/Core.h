#pragma once

#ifdef LE_PLATFORM_WINDOWS
	#ifdef LE_DYNAMIC_LINK
		#ifdef LE_BUILD_DLL
			#define LETGEN_API __declspec(dllexport)
		#else
			#define LETGEN_API __declspec(dllimport)
		#endif
	#else
		#define LETGEN_API
	#endif
#else
	#error Only supports Windows so far!
#endif

#ifdef LE_DEBUG
	#define LE_ENABLE_ASSERTS 1
#endif

#if LE_ENABLE_ASSERTS
	#define LE_ASSERT(x, ...) { if(!(x)) { Log::Error("Assertion Failed {0}", __VA_ARGS__); __debugbreak(); } }
	#define LE_CORE_ASSERT(x, ...) { if(!(x)) { Log::CoreError("Assertion Failed {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define LE_ASSERT(x, ...)
	#define LE_CORE_ASSERT(x, ...)
#endif

#define LE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)


constexpr int Bit(const int offset) { return 1 << offset; }
