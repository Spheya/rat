#pragma once

#include <format> // IWYU pragma: export
#include <string_view>
#include <type_traits>
#include <utility>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>

namespace glm {
	template<length_t L, typename T, qualifier Q>
	struct vec;

	template<length_t C, length_t R, typename T, qualifier Q>
	struct mat;
} // namespace glm

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

namespace std {
	template<glm::length_t L, typename T, glm::qualifier Q>
	struct formatter<glm::vec<L, T, Q>> {
		template<typename ParseContext>
		constexpr auto parse(ParseContext& ctx) {
			return ctx.begin();
		}

		template<typename FormatContext>
		auto format(const glm::vec<L, T, Q>& v, FormatContext& ctx) const {
			auto it = format_to(ctx.out(), "[");
			for(glm::length_t i = 0; i < L; ++i) {
				if constexpr(std::is_floating_point_v<T>) {
					if(i == L - 1)
						it = format_to(it, "{:.4f}", v[i]);
					else
						it = format_to(it, "{:.4f}, ", v[i]);
				} else {
					if(i == L - 1)
						it = format_to(it, "{}", v[i]);
					else
						it = format_to(it, "{}, ", v[i]);
				}
			}
			return format_to(it, "]");
		}
	};

	template<glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
	struct formatter<glm::mat<C, R, T, Q>> {
		template<typename ParseContext>
		constexpr auto parse(ParseContext& ctx) {
			return ctx.begin();
		}

		template<typename FormatContext>
		auto format(const glm::mat<C, R, T, Q>& m, FormatContext& ctx) const {
			auto it = format_to(ctx.out(), "[");
			for(glm::length_t i = 0; i < R; ++i) {
				auto row = glm::row(m, i);
				if(i == R - 1)
					it = format_to(it, "{}", row);
				else
					it = format_to(it, "{}, ", row);
			}
			return format_to(it, "]");
		}
	};

	template<typename T, glm::qualifier Q>
	struct formatter<glm::qua<T, Q>> {
		template<typename ParseContext>
		constexpr auto parse(ParseContext& ctx) {
			return ctx.begin();
		}

		template<typename FormatContext>
		auto format(const glm::qua<T, Q>& q, FormatContext& ctx) const {
			return format_to(ctx.out(), "{{w:{:.4f}, x:{:.4f}, y:{:.4f}, z:{:.4f}}}", q.w, q.x, q.y, q.z);
		}
	};
} // namespace std
