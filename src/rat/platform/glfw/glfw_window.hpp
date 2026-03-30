#pragma once

#include <glm/glm.hpp>

#include "rat/core/window.hpp"

struct GLFWwindow;

namespace rat::glfw {

	class Window final : public rat::Window {
	public:
		Window(GLFWwindow* window);
		Window(Window&) = delete;
		Window& operator=(Window&) = delete;
		Window(Window&& other) noexcept;
		Window& operator=(Window&& other) noexcept;
		~Window() override;

		[[nodiscard]] glm::uvec2 getSize() const override;
		[[nodiscard]] glm::ivec2 getPosition() const override;

		[[nodiscard]] const char* getTitle() const override;
		void setTitle(const char* title) override;

		[[nodiscard]] bool isCloseRequested() const override;

		[[nodiscard]] bool isValid() const { return m_window; }

	private:
		GLFWwindow* m_window;
	};

} // namespace rat::glfw
