#include "engine.hpp"

#include <cassert>

#include <glm/ext/matrix_transform.hpp>

#include "rat/rendering/drawable.hpp"
#include "rat/rendering/vertex.hpp"

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

		Vertex vertices[] = {
			{ .position = glm::vec3(0.0f,  0.5f,  0.0f),
             .normal = glm::vec3(0.0f, 0.0f, 1.0f),
             .uv = glm::vec2(0.5f, 1.0f),
             .color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
             .tangent = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) },
			{ .position = glm::vec3(-0.5f, -0.5f, 0.0f),
             .normal = glm::vec3(0.0f, 0.0f, 1.0f),
             .uv = glm::vec2(0.0f, 0.0f),
             .color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
             .tangent = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) },
			{ .position = glm::vec3(0.5f,  -0.5f, 0.0f),
             .normal = glm::vec3(0.0f, 0.0f, 1.0f),
             .uv = glm::vec2(1.0f, 0.0f),
             .color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
             .tangent = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) }
		};

		unsigned indices[] = { 0, 1, 2 };

		tri = m_graphicsContext->createMesh(vertices, indices);
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
		m_graphicsContext->beginFrame();

		Drawable drawables[] = {
			{ .mesh = tri, .matrix = glm::identity<glm::mat4>() }
		};
		m_graphicsContext->draw(drawables);

		m_graphicsContext->endFrame();
	}

	// NOLINTBEGIN
	bool Engine::isCloseRequested() const {
		return false;
	}
	// NOLINTEND

} // namespace rat
