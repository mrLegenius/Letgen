#pragma once

#include <memory>

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

namespace Letgen
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
	
	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
