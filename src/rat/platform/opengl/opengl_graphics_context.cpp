#include "opengl_graphics_context.hpp"

#include <glad/glad.h>

#include "opengl_mesh.hpp"
#include "rat/core/logger.hpp"
#include "rat/platform/glfw/glfw.hpp"

namespace rat {

	OpenGLGraphicsContext::OpenGLGraphicsContext(const ApplicationInfo& appInfo) :
	    BaseGraphicsContext(GraphicsBackend::OpenGL3), m_glContext(nullptr) {
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

	OpenGLGraphicsContext::~OpenGLGraphicsContext() {
		m_window.reset();
		glfwTerminate();
	}

	bool OpenGLGraphicsContext::isValid() const {
		return m_window != nullptr;
	}

	bool OpenGLGraphicsContext::isCloseRequested() const {
		return m_window->isCloseRequested();
	}

	void OpenGLGraphicsContext::beginFrame() {
		glfwPollEvents();
	}

	void OpenGLGraphicsContext::endFrame() {
		glfwSwapBuffers(m_glContext);
	}

	Mesh* OpenGLGraphicsContext::createMesh(std::span<const Vertex> vertices, std::span<const unsigned> indices) {
		auto* mesh = new OpenGLMesh();

		mesh->setVertices(vertices);
		mesh->setIndices(indices);

		return mesh;
	}

	void OpenGLGraphicsContext::destroyMesh(Mesh* mesh) {
		delete static_cast<OpenGLMesh*>(mesh);
	}

	void OpenGLGraphicsContext::render(const Drawable* drawables, unsigned drawableCount) {
		for(unsigned i = 0; i < drawableCount; ++i) {
			const auto* mesh = static_cast<const OpenGLMesh*>(drawables->mesh);
			glBindVertexArray(mesh->m_vertexBuffer);
			glDrawElements(GL_TRIANGLES, mesh->numIndices, GL_UNSIGNED_INT, nullptr);
		}
		glBindVertexArray(0);
	}

} // namespace rat
