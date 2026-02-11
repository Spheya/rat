#pragma once

#include <concepts>
#include <format>
#include <functional>
#include <source_location>
#include <string_view>
#include <type_traits>

namespace rat {

	enum class LogLevel { None = 0, Error = 1, Warn = 2, Info = 3, Trace = 4 };

	template<typename... Args>
	struct LogMessageImpl {
		template<typename T>
		    requires std::convertible_to<const T&, std::basic_string_view<char>>
		consteval LogMessageImpl(T const& message, std::source_location location = std::source_location::current()) :
		    message(message), location(location) {}

		std::format_string<Args...> message;
		std::source_location location;
	};

	template<typename... Args>
	using LogMessage = LogMessageImpl<std::type_identity_t<Args>...>;

	void setMessageCallback(std::function<void(std::string_view, std::source_location, LogLevel)> callback);
	void message(std::string_view message, std::source_location location, LogLevel level);

#ifndef RAT_STRIP_LOGGER

	template<typename... Args>
	inline void log(LogMessage<Args...> message, Args&&... args) {
		rat::message(std::format(message.message, std::forward<Args&&>(args)...), message.location, LogLevel::Trace);
	}

	template<typename... Args>
	inline void info(LogMessage<Args...> message, Args&&... args) {
		rat::message(std::format(message.message, std::forward<Args&&>(args)...), message.location, LogLevel::Info);
	}

	template<typename... Args>
	inline void warn(LogMessage<Args...> message, Args&&... args) {
		rat::message(std::format(message.message, std::forward<Args&&>(args)...), message.location, LogLevel::Warn);
	}

	template<typename... Args>
	inline void error(LogMessage<Args...> message, Args&&... args) {
		rat::message(std::format(message.message, std::forward<Args&&>(args)...), message.location, LogLevel::Error);
	}

	template<typename T>
	    requires(!std::convertible_to<const T&, std::basic_string_view<char>>)
	inline void log(const T& value, std::source_location location = std::source_location::current()) {
		message(std::format("{}", value), location, LogLevel::Trace);
	}

	template<typename T>
	    requires(!std::convertible_to<const T&, std::basic_string_view<char>>)
	inline void info(const T& value, std::source_location location = std::source_location::current()) {
		message(std::format("{}", value), location, LogLevel::Info);
	}

	template<typename T>
	    requires(!std::convertible_to<const T&, std::basic_string_view<char>>)
	inline void warn(const T& value, std::source_location location = std::source_location::current()) {
		message(std::format("{}", value), location, LogLevel::Warn);
	}

	template<typename T>
	    requires(!std::convertible_to<const T&, std::basic_string_view<char>>)
	inline void error(const T& value, std::source_location location = std::source_location::current()) {
		message(std::format("{}", value), location, LogLevel::Error);
	}

#else

	template<typename... Args>
	inline void log([[maybe_unused]] LogMessage<Args...> message, [[maybe_unused]] Args&&... args) {}

	template<typename... Args>
	inline void info([[maybe_unused]] LogMessage<Args...> message, [[maybe_unused]] Args&&... args) {}

	template<typename... Args>
	inline void warn([[maybe_unused]] LogMessage<Args...> message, [[maybe_unused]] Args&&... args) {}

	template<typename... Args>
	inline void error([[maybe_unused]] LogMessage<Args...> message, [[maybe_unused]] Args&&... args) {}

	template<typename T>
	    requires(!std::convertible_to<const T&, std::basic_string_view<char>>)
	inline void log([[maybe_unused]] const T& value, [[maybe_unused]] std::source_location location = std::source_location::current()) {}

	template<typename T>
	    requires(!std::convertible_to<const T&, std::basic_string_view<char>>)
	inline void info([[maybe_unused]] const T& value, [[maybe_unused]] std::source_location location = std::source_location::current()) {}

	template<typename T>
	    requires(!std::convertible_to<const T&, std::basic_string_view<char>>)
	inline void warn([[maybe_unused]] const T& value, [[maybe_unused]] std::source_location location = std::source_location::current()) {}

	template<typename T>
	    requires(!std::convertible_to<const T&, std::basic_string_view<char>>)
	inline void error([[maybe_unused]] const T& value, [[maybe_unused]] std::source_location location = std::source_location::current()) {}

#endif

} // namespace rat
