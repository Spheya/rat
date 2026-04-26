#pragma once

// Export this because otherwise you need to include it everytime you want to log something
// Todo: maybe also be able to log const char* ? That would allow removal of this export
#include <format> // IWYU pragma : export

namespace rat {
	enum class LogLevel { Log, Info, Warn, Error };

#ifdef RAT_DEV_TOOLS

	void message(const char* message, LogLevel level);

	template<typename... T>
	void log(std::format_string<T...> fmt, T&&... args) {
		message(std::format(fmt, std::forward<T&&>(args)...).c_str(), LogLevel::Log);
	}

	template<typename... T>
	void warn(std::format_string<T...> fmt, T&&... args) {
		message(std::format(fmt, std::forward<T&&>(args)...).c_str(), LogLevel::Warn);
	}

	template<typename... T>
	void error(std::format_string<T...> fmt, T&&... args) {
		message(std::format(fmt, std::forward<T&&>(args)...).c_str(), LogLevel::Error);
	}

#else

	template<typename... T>
	void log([[maybe_unused]] std::format_string<T...> fmt, [[maybe_unused]] T&&... args) {}

	template<typename... T>
	void warn([[maybe_unused]] std::format_string<T...> fmt, [[maybe_unused]] T&&... args) {}

	template<typename... T>
	void error([[maybe_unused]] std::format_string<T...> fmt, [[maybe_unused]] T&&... args) {}

#endif

} // namespace rat
