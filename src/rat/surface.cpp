#include "surface.hpp"

#include <memory>

#include "platform/glfw/glfw_window.hpp"

namespace rat {

	std::unique_ptr<Surface> createSurface(unsigned requestWidth, unsigned requestHeight, const char* title) {
		return createSurface(glm::uvec2(requestWidth, requestHeight), title);
	}

	std::unique_ptr<Surface> createSurface(glm::uvec2 requestSize, const char* title) {
		return std::make_unique<glfw::Window>(requestSize, title);
	}

} // namespace rat
