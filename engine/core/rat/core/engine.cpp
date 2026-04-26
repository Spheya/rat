#include "engine.hpp"

#include <cassert>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "logger.hpp"

namespace rat {

	Engine* Engine::s_engine = nullptr;

	Engine::Engine(EditorContext* editorContext) : m_editorContext(editorContext), m_graphicsContext(nullptr) {
#if defined(RAT_GLFW) && !defined(RAT_EDITOR)
		glfwInit();
#endif
		m_graphicsContext = std::make_unique<opengl::GraphicsContext>(editorContext); // NOLINT(cppcoreguidelines-prefer-member-initializer)
	}

	Engine::~Engine() {
#if defined(RAT_GLFW) && !defined(RAT_EDITOR)
		glfwTerminate();
#endif
	}

	void Engine::initialize(EditorContext* editorContext) {
		assert(s_engine == nullptr);
		s_engine = new Engine(editorContext);
	}

	void Engine::terminate() {
		delete s_engine;
	}

	// NOLINTBEGIN
	void Engine::tick() {
#ifdef RAT_GLFW
		glfwPollEvents();
#endif
		rat::log("running the engine!");
		rat::warn("running the engine!");
		rat::error("running the engine!");
	}

	bool Engine::isCloseRequested() const {
		return false;
	}
	// NOLINTEND

} // namespace rat
