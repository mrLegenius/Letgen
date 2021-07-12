#include "Logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Letgen
{
	namespace Log
	{
		std::shared_ptr<spdlog::logger> Logger::_internalLogger;
		std::shared_ptr<spdlog::logger> Logger::_externalLogger;

		void Logger::Init()
		{
			spdlog::set_pattern("%^[%T] %n: %v%$");

			_internalLogger = spdlog::stdout_color_mt("LEGEN");
			//TODO: make level changeable
			_internalLogger->set_level(spdlog::level::trace);

			_externalLogger = spdlog::stdout_color_mt("APP");
			_externalLogger->set_level(spdlog::level::trace);
		}
	}
}