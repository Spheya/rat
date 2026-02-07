#pragma once

#include "rat/window.hpp"

struct GLFWwindow;

namespace rat::glfw {

	class Window final : public rat::Window {
	public:
		Window(unsigned width, unsigned height, const char* title);
		Window(glm::uvec2 size, const char* title);
		Window(Window&& other) noexcept;
		Window& operator=(Window&& other) noexcept;
		virtual ~Window();

		virtual glm::uvec2 getSize() const override;
		virtual glm::ivec2 getPosition() const override;

		virtual const char* getTitle() const override;
		virtual void setTitle(const char* title) override;

	private:
		GLFWwindow* m_window;
	};

} // namespace rat::glfw
