#pragma once

#include <format> // IWYU oragma: export
#include <string_view>
#include <utility>

namespace rat {

	enum class LogLevel { Log, Warn, Error };

	void message(std::string_view message, LogLevel level);

#ifndef RAT_STRIP_LOGGER

	template<typename... Args>
	inline void log(std::format_string<Args...> fmt, Args&&... args) {
		rat::message(std::format(fmt, std::forward<Args&&>(args)...), LogLevel::Log);
	}

	template<typename... Args>
	inline void warn(std::format_string<Args...> fmt, Args&&... args) {
		rat::message(std::format(fmt, std::forward<Args&&>(args)...), LogLevel::Warn);
	}

	template<typename... Args>
	inline void error(std::format_string<Args...> fmt, Args&&... args) {
		rat::message(std::format(fmt, std::forward<Args&&>(args)...), LogLevel::Error);
	}

#else

	template<typename... Args>
	inline void log([[maybe_unused]] LogMessage<Args...> message, [[maybe_unused]] Args&&... args) {}

	template<typename... Args>
	inline void warn([[maybe_unused]] LogMessage<Args...> message, [[maybe_unused]] Args&&... args) {}

	template<typename... Args>
	inline void error([[maybe_unused]] LogMessage<Args...> message, [[maybe_unused]] Args&&... args) {}

#endif

} // namespace rat
