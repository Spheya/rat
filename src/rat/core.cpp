#include "core.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace rat {

	void intialize() {
		glfwInit();
	}

	void terminate() {
		glfwTerminate();
	}

	void pollEvents() {
		glfwPollEvents();
	}

} // namespace rat
