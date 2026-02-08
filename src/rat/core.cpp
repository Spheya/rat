#include "core.hpp"
#include "logger.hpp"
#include "platform/glfw/glfw.hpp"

namespace rat {

#ifndef RAT_STRIP_LOGGER
	static void glfwErrorHandler(int errCode, const char* message) {
		rat::error("{}({:#010x}) : {}", rat::glfw::getErrString(errCode), errCode, message);
	}
#endif

	bool intialize() {
#ifndef RAT_STRIP_LOGGER
		glfwSetErrorCallback(glfwErrorHandler);
#endif

		if(!glfwInit()) {
			rat::error("Could not initialize GLFW");
			return false;
		}

		rat::info("                                   _..----.._    _       ");
		rat::info("                                 ./  .--.    \"-.(0)_     ");
		rat::info("                       -.__-'\"'=:|   ,  _)_ \\__ .   '-.. ");
		rat::info("                                  '''------'---''---'-\"  ");
		rat::info("                                              $$$\\       ");
		rat::info("                         $$$\\$$$\\  $$$$$$$\\  $$$$$$\\     ");
		rat::info("                         $$$$$$$$\\ \\    $$$\\ \\$$$  _|    ");
		rat::info("                         $$$  -___|$$$$$$$$ | $$$ |      ");
		rat::info("                         $$$ |    $$$   $$$ | $$$ |$$$\\  ");
		rat::info("                         $$$ |    \\$$$$$$$$ | \\$$$$$$  | ");
		rat::info("                         \\___|     \\________|  \\______/  ");
		rat::info("                                                         ");
		rat::info("Rat Initialized!");
		return true;
	}

	void terminate() {
		glfwTerminate();
		rat::info("Rat Terminated!");
	}

	void pollEvents() {
		glfwPollEvents();
	}

} // namespace rat
