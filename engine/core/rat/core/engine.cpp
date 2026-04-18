#include "engine.hpp"

#include <cassert>

#include <GLFW/glfw3.h>

#include "editorcontext.hpp"
#include "logger.hpp"

namespace rat {

	Engine* Engine::s_engine = nullptr;

	Engine::Engine(EditorContext* editorContext) : m_editorContext(editorContext), m_graphicsContext(nullptr) {
#if defined(RAT_GLFW) && !defined(RAT_EDITOR)
		glfwInit();
#endif
		m_graphicsContext = std::make_unique<opengl::GraphicsContext>(editorContext);
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

	void Engine::tick() {
#ifdef RAT_GLFW
		glfwPollEvents();
#endif
		logMessage("running the engine!");
	}

	bool Engine::isCloseRequested() const {
		return false;
	}

} // namespace rat
