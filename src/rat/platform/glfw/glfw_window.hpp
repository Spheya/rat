#pragma once

#include "rat/window.hpp"

struct GLFWwindow;

namespace rat::glfw {

	class Window final : public rat::Window {
	public:
		Window(GLFWwindow* window);
		Window(Window&& other) noexcept;
		Window& operator=(Window&& other) noexcept;
		virtual ~Window();


		virtual glm::uvec2 getSize() const override;
		virtual glm::ivec2 getPosition() const override;

		virtual const char* getTitle() const override;
		virtual void setTitle(const char* title) override;

		virtual bool isCloseRequested() const override;

		bool isValid() const { return m_window; }

	private:
		GLFWwindow* m_window;
	};

} // namespace rat::glfw
