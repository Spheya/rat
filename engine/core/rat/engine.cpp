#include "engine.hpp"

#include <cassert>

#include "logger.hpp"

namespace rat {

	Engine* Engine::s_engine = nullptr;

	Engine::Engine(GLFWwindow* /*window*/) {}
	Engine::~Engine() = default;

	void Engine::initialize(GLFWwindow* window) {
		assert(s_engine == nullptr);
		s_engine = new Engine(window);
	}

	void Engine::terminate() {
		delete s_engine;
	}

	void Engine::run() {
		logMessage("running the engine!");
	}

} // namespace rat
