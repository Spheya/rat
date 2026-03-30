#pragma once

#include <format> // IWYU pragma: export
#include <string_view>
#include <utility>

#include <glm/glm.hpp>

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

template<glm::length_t L, typename T, glm::qualifier Q>
struct std::formatter<glm::vec<L, T, Q>> {
	template<typename ParseContext>
	constexpr auto parse(ParseContext& ctx) {
		return ctx.begin();
	}

	template<typename FormatContext>
	auto format(const glm::vec<L, T, Q>& v, FormatContext& ctx) const {
		static_assert(L > 0 && L <= 4);
		if constexpr(L == 1) return format_to(ctx.out(), "[ {} ]", v.x);
		if constexpr(L == 2) return format_to(ctx.out(), "[ {}, {} ]", v.x, v.y);
		if constexpr(L == 3) return format_to(ctx.out(), "[ {}, {}, {} ]", v.x, v.y, v.z);
		if constexpr(L == 4) return format_to(ctx.out(), "[ {}, {}, {}, {} ]", v.x, v.y, v.z, v.w);
	}
};
