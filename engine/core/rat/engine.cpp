#include "engine.hpp"

#include <cassert>

#include "logger.hpp"

namespace rat {

	Engine* Engine::s_engine = nullptr;

	void Engine::initialize() {
		assert(s_engine == nullptr);
		s_engine = new Engine();
	}

	void Engine::terminate() {
		delete s_engine;
	}

	void Engine::run() {
		logMessage("running the engine!");
	}

} // namespace rat
