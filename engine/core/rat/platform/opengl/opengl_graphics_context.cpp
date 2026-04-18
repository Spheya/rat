#include "opengl_graphics_context.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "rat/core/editorcontext.hpp"

namespace rat::opengl {

	GraphicsContext::GraphicsContext(EditorContext* editorContext) {
		if(editorContext->window) {
			m_window = editorContext->window;
		} else {
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			m_window = glfwCreateWindow(640, 480, "Rat Engine", nullptr, nullptr);
			editorContext->window = m_window;
		}
	}

	GraphicsContext::~GraphicsContext() {
		glfwDestroyWindow(m_window);
	}

} // namespace rat::opengl
