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

#define LE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

constexpr int Bit(const int offset) { return 1 << offset; }
