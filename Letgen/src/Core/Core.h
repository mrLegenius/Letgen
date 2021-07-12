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

