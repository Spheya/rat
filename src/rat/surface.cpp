#include "surface.hpp"

#include <memory>
#include <utility>

#include "logger.hpp"
#include "platform/glfw/glfw_window.hpp"

namespace rat {

	std::unique_ptr<Surface> createSurface(unsigned requestWidth, unsigned requestHeight, const char* title) {
		return createSurface(glm::uvec2(requestWidth, requestHeight), title);
	}

	std::unique_ptr<Surface> createSurface(glm::uvec2 requestSize, const char* title) {
		auto window = std::make_unique<glfw::Window>(requestSize, title);
		if(!window->isValid()) {
			rat::error("Could not create a GLFW window");
			return nullptr;
		}
		return std::move(window);
	}

} // namespace rat
