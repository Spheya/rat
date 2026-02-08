#include "glfw_window.hpp"
#include "glfw.hpp"

namespace rat::glfw {

	Window::Window(unsigned width, unsigned height, const char* title) : Window(glm::uvec2(width, height), title) {}

	Window::Window(glm::uvec2 size, const char* title) {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		m_window = glfwCreateWindow(size.x, size.y, title, nullptr, nullptr); // NOLINT
	}

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

	void Window::swapBuffers() {
		glfwSwapBuffers(m_window);
	}

} // namespace rat::glfw
