#include "pch.h"
#include "Letgen/Core/Logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Letgen::Log
{
	std::shared_ptr<spdlog::logger> Logger::m_CoreLogger;
	std::shared_ptr<spdlog::logger> Logger::m_Logger;

	void Logger::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		m_CoreLogger = spdlog::stdout_color_mt("LETGEN");
		//TODO: make level changeable
		m_CoreLogger->set_level(spdlog::level::trace);

		m_Logger = spdlog::stdout_color_mt("APP");
		m_Logger->set_level(spdlog::level::trace);
	}
}
