#include "opengl_graphics_context.hpp"

#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "opengl_mesh.hpp"
#include "rat/core/editorcontext.hpp"
#include "rat/platform/opengl/opengl_mesh.hpp"

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
		glfwMakeContextCurrent(m_window);
		gladLoadGL(glfwGetProcAddress);

#ifdef RAT_EDITOR // todo: also run in dev builds
		gladInstallGLDebug();
#endif
	}

	GraphicsContext::~GraphicsContext() {
		glfwDestroyWindow(m_window);
	}

	void GraphicsContext::beginFrame() {}

	void GraphicsContext::endFrame() {
		glfwSwapBuffers(m_window);
	}

	void GraphicsContext::draw(std::span<const Drawable> drawables) {
		for(const auto& drawable : drawables) {
			glBindVertexArray(drawable.mesh->getVao());
			glDrawElements(GL_TRIANGLES, GLsizei(drawable.mesh->getIndexCount()), GL_UNSIGNED_INT, nullptr);
		}
		glBindVertexArray(0);
	}

	Mesh* GraphicsContext::createMesh(std::span<const Vertex> vertices, std::span<const uint32_t> indices) {
		return new Mesh(vertices, indices);
	}

	void GraphicsContext::destroyMesh(Mesh* mesh) {
		delete mesh;
	}

} // namespace rat::opengl
