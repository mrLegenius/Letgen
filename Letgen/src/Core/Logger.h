#pragma once
#include "Core.h"

#include "spdlog/spdlog.h"

//Able to log custom classes
#include "spdlog/fmt/ostr.h"
namespace Letgen
{
	namespace Log
	{
		class LETGEN_API Logger
		{
		public:
			static void Init();

			static std::shared_ptr<spdlog::logger>& GetInternalLogger() { return _internalLogger; }
			static std::shared_ptr<spdlog::logger>& GetExternalLogger() { return _externalLogger; }

		private:
			static std::shared_ptr<spdlog::logger> _internalLogger;
			static std::shared_ptr<spdlog::logger> _externalLogger;
		};
		
#pragma region ***Engine logging***
#ifdef LE_BUILD_DLL
		template <typename T> constexpr void InnerTrace(T message) { Logger::GetInternalLogger()->trace(message); }
		template <typename T> constexpr void InnerDebug(T message) { Logger::GetInternalLogger()->debug(message); }
		template <typename T> constexpr void InnerInfo(T message) { Logger::GetInternalLogger()->info(message); }
		template <typename T> constexpr void InnerWarn(T message) { Logger::GetInternalLogger()->warn(message); }
		template <typename T> constexpr void InnerError(T message) { Logger::GetInternalLogger()->error(message); }
		template <typename T> constexpr void InnerCritical(T message) { Logger::GetInternalLogger()->critical(message); }

		template<typename FormatString, typename... Args> constexpr void InnerTrace(const FormatString& format, Args&&...args)
		{
			Logger::GetInternalLogger()->trace(format, std::forward<Args>(args)...);
		}
		template<typename FormatString, typename... Args> constexpr void InnerDebug(const FormatString& format, Args&&...args) {
			Logger::GetInternalLogger()->debug(format, std::forward<Args>(args)...);
		}
		template<typename FormatString, typename... Args> constexpr void InnerInfo(const FormatString& format, Args&&...args) {
			Logger::GetInternalLogger()->info(format, std::forward<Args>(args)...);
		}
		template<typename FormatString, typename... Args> constexpr void InnerWarn(const FormatString& format, Args&&...args) {
			Logger::GetInternalLogger()->warn(format, std::forward<Args>(args)...);
		}
		template<typename FormatString, typename... Args> constexpr void InnerError(const FormatString& format, Args&&...args) {
			Logger::GetInternalLogger()->error(format, std::forward<Args>(args)...);
		}
		template<typename FormatString, typename... Args> constexpr void InnerCritical(const FormatString& format, Args&&...args) {
			Logger::GetInternalLogger()->critical(format, std::forward<Args>(args)...);
		}
#endif
#pragma endregion
		
#pragma region ***Client logging***
		template <typename T> constexpr void Trace(T message) { Logger::GetExternalLogger()->trace(message); }
		template <typename T> constexpr void Debug(T message) { Logger::GetExternalLogger()->debug(message); }
		template <typename T> constexpr void Info(T message) { Logger::GetExternalLogger()->info(message); }
		template <typename T> constexpr void Warn(T message) { Logger::GetExternalLogger()->warn(message); }
		template <typename T> constexpr void Error(T message) { Logger::GetExternalLogger()->error(message); }
		template <typename T> constexpr void Critical(T message) { Logger::GetExternalLogger()->critical(message); }

		
		template<typename FormatString, typename... Args> constexpr void Trace(const FormatString& format, Args&&...args) {
			Logger::GetExternalLogger()->trace(format, std::forward<Args>(args)...);
		}
		template<typename FormatString, typename... Args> constexpr void Debug(const FormatString& format, Args&&...args) {
			Logger::GetExternalLogger()->debug(format, std::forward<Args>(args)...);
		}
		template<typename FormatString, typename... Args> constexpr void Info(const FormatString& format, Args&&...args) {
			Logger::GetExternalLogger()->info(format, std::forward<Args>(args)...);
		}
		template<typename FormatString, typename... Args> constexpr void Warn(const FormatString& format, Args&&...args) {
			Logger::GetExternalLogger()->warn(format, std::forward<Args>(args)...);
		}
		template<typename FormatString, typename... Args> constexpr void Error(const FormatString& format, Args&&...args) {
			Logger::GetExternalLogger()->error(format, std::forward<Args>(args)...);
		}
		template<typename FormatString, typename... Args> constexpr void Critical(const FormatString& format, Args&&...args) {
			Logger::GetExternalLogger()->critical(format, std::forward<Args>(args)...);
		}
#pragma endregion 

	}
}