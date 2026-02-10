#include "glfw_window.hpp"
#include "glfw.hpp"

namespace rat::glfw {

	Window::Window(GLFWwindow* window) : m_window(window) {}

	Window::Window(Window&& other) noexcept : m_window(other.m_window) {
		other.m_window = nullptr;
	}

	Window& Window::operator=(Window&& other) noexcept {
		if(m_window) glfwDestroyWindow(m_window);
		m_window = other.m_window;
		other.m_window = nullptr;
		return *this;
	}

	Window::~Window() {
		if(m_window) glfwDestroyWindow(m_window);
	}

	glm::uvec2 Window::getSize() const {
		int w, h;
		float sx, sy;
		glfwGetWindowSize(m_window, &w, &h);
		glfwGetWindowContentScale(m_window, &sx, &sy);
		return glm::uvec2(w * sx, h * sy);
	}

	glm::ivec2 Window::getPosition() const {
		glm::ivec2 position;
		glfwGetWindowPos(m_window, &position.x, &position.y);
		return position;
	}

	const char* Window::getTitle() const {
		return glfwGetWindowTitle(m_window);
	}

	void Window::setTitle(const char* title) {
		glfwSetWindowTitle(m_window, title);
	}

	bool Window::isCloseRequested() const {
		return glfwWindowShouldClose(m_window);
	}

} // namespace rat::glfw
