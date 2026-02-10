#include "opengl_graphics_context.hpp"

#include <glad/glad.h>

#include "rat/logger.hpp"
#include "rat/platform/glfw/glfw.hpp"

namespace rat::opengl {

	GraphicsContext::GraphicsContext(const ApplicationInfo& appInfo) : rat::GraphicsContext(GraphicsBackend::OpenGL3), m_glContext(nullptr) {
		glfw::setupErrorHandler();
		if(glfwInit() == GLFW_FALSE) {
			rat::error("Could not initialize GLFW");
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		m_glContext = glfw::createWindow(appInfo);
		if(m_glContext == nullptr) {
			rat::error("Could not create a window");
			return;
		}
		glfwMakeContextCurrent(m_glContext);
		if(!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))) {
			rat::error("Could not load OpenGL");
			return;
		}

#ifndef RAT_STRIP_LOGGER
		int major, minor, rev;
		glfwGetVersion(&major, &minor, &rev);
		rat::info("GLFW version: {}.{}.{}", major, minor, rev);
		rat::info("OpenGL version: {}", (const char*)glGetString(GL_VERSION)); // NOLINT
		rat::info("OpenGL vendor: {}", (const char*)glGetString(GL_VENDOR));   // NOLINT
		rat::info("OpenGL device: {}", (const char*)glGetString(GL_RENDERER)); // NOLINT
#endif

		m_window = std::make_unique<glfw::Window>(m_glContext);
		renderTarget = m_window.get();
	}

	GraphicsContext::~GraphicsContext() {
		m_window.reset();
		glfwTerminate();
	}

	bool GraphicsContext::isValid() const {
		return m_window != nullptr;
	}

	bool GraphicsContext::isCloseRequested() const {
		return m_window->isCloseRequested();
	}

	void GraphicsContext::beginFrame() {
		glfwPollEvents();
	}

	void GraphicsContext::endFrame() {
		glfwSwapBuffers(m_glContext);
	}

} // namespace rat::opengl
