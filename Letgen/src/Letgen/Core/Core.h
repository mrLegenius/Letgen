#pragma once

#include <memory>

#ifdef LET_PLATFORM_WINDOWS
	#ifdef LET_DYNAMIC_LINK
		#ifdef LET_BUILD_DLL
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

#define LET_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

constexpr int Bit(const int offset) { return 1 << offset; }

namespace Letgen
{
	// ///////////////////////////////////////////////////////////
	// -- Scope --------------------------------------------------
	// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	
	template<typename T>
	using Scope = std::unique_ptr<T>;
	
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
	
	template<typename T>
	constexpr Scope<T> CreateScope(T object)
	{
		return std::make_unique<T>(std::move(object));
	}

	template<typename T, typename List>
	constexpr Scope<T> CreateScope(std::initializer_list<List> list)
	{
		return Scope<T>{ new T(list) };
	}
	
	// ///////////////////////////////////////////////////////////
	// -- Ref ----------------------------------------------------
	// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	
	template<typename T>
	using Ref = std::shared_ptr<T>;
	
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
	
	template<typename T>
	constexpr Ref<T> CreateRef(T object)
	{
		return std::make_shared<T>(std::move(object));
	}

	template<typename T, typename List>
	constexpr Ref<T> CreateRef(std::initializer_list<List> list)
	{
		return Ref<T>{ new T(list) };
	}
}
