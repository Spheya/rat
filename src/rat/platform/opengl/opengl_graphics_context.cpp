#include "opengl_graphics_context.hpp"

#include <span>

#include <glad/glad.h>

#include "opengl_mesh.hpp"
#include "opengl_pipeline.hpp"
#include "opengl_shader.hpp"
#include "rat/core/logger.hpp"
#include "rat/platform/glfw/glfw.hpp"

namespace rat {

	namespace {
		struct CameraBuffer {
			glm::mat4 matrix_p;
			glm::mat4 matrix_v;
		};
	} // namespace

	OpenGLGraphicsContext::OpenGLGraphicsContext(const ApplicationInfo& appInfo) :
	    BaseGraphicsContext(GraphicsBackend::OpenGL3), m_glContext(nullptr), m_instanceBuffer(0), m_cameraBuffer(0) {
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

		glGenBuffers(2, &m_instanceBuffer);
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_cameraBuffer);
	}

	OpenGLGraphicsContext::~OpenGLGraphicsContext() {
		glDeleteBuffers(1, &m_instanceBuffer);
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
		auto* mesh = new OpenGLMesh(m_instanceBuffer);

		mesh->setVertices(vertices);
		mesh->setIndices(indices);

		return mesh;
	}

	void OpenGLGraphicsContext::destroyMesh(Mesh* mesh) {
		delete static_cast<OpenGLMesh*>(mesh);
	}

	Shader* OpenGLGraphicsContext::createShader(const char* vertex, const char* fragment) {
		return new OpenGLShader(vertex, fragment);
	}

	void OpenGLGraphicsContext::destroyShader(Shader* shader) {
		delete static_cast<OpenGLShader*>(shader);
	}

	Pipeline* OpenGLGraphicsContext::createPipeline(const Shader* shader, CullMode cullMode, DepthTestMode depthTestMode, bool depthWriteEnabled) {
		return new OpenGLPipeline(shader, cullMode, depthTestMode, depthWriteEnabled);
	}

	void OpenGLGraphicsContext::destroyPipeline(Pipeline* pipeline) {
		delete static_cast<OpenGLPipeline*>(pipeline);
	}

	void OpenGLGraphicsContext::render(const Camera& camera, std::span<const Drawable> drawables) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		CameraBuffer cam{ .matrix_p = camera.projectionMatrix, .matrix_v = camera.viewMatrix };
		glBindBuffer(GL_UNIFORM_BUFFER, m_cameraBuffer);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(CameraBuffer), &cam, GL_DYNAMIC_DRAW);
		renderDrawables(drawables);
	}

	void OpenGLGraphicsContext::renderDrawables(std::span<const Drawable> drawables) {
		if(drawables.empty()) return;

		std::vector<glm::mat4> instanceBuffer(drawables.size());
		for(size_t i = 0; i < drawables.size(); ++i) instanceBuffer[i] = drawables[i].matrix;

		glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);
		glBufferData(GL_ARRAY_BUFFER, instanceBuffer.size() * sizeof(glm::mat4), instanceBuffer.data(), GL_STREAM_DRAW);

		const auto* boundPipeline = static_cast<const OpenGLPipeline*>(drawables.front().material->pipeline);
		const auto* boundMesh = static_cast<const OpenGLMesh*>(drawables.front().mesh);

		glBindVertexArray(boundMesh->m_vao);
		bindPipeline(boundPipeline);

		size_t batchStart = 0;
		for(size_t i = 1; i < drawables.size(); ++i) {
			const auto* newPipeline = static_cast<const OpenGLPipeline*>(drawables[i].material->pipeline);
			const auto* newMesh = static_cast<const OpenGLMesh*>(drawables[i].mesh);

			if(newPipeline != boundPipeline || newMesh != boundMesh) {
				glDrawElementsInstanced(GL_TRIANGLES, boundMesh->indexCount(), GL_UNSIGNED_INT, nullptr, i - batchStart);
				batchStart = i;

				if(newPipeline != boundPipeline) {
					boundPipeline = newPipeline;
					bindPipeline(boundPipeline);
				}

				if(newMesh != boundMesh) {
					boundMesh = newMesh;
					glBindVertexArray(boundMesh->m_vao);
				}
			}
		}
		glDrawElementsInstanced(GL_TRIANGLES, boundMesh->indexCount(), GL_UNSIGNED_INT, nullptr, GLsizei(drawables.size() - batchStart));

		glBindVertexArray(0);
	}

	void OpenGLGraphicsContext::bindPipeline(const Pipeline* pipeline) {
		const auto* oglPipeline = static_cast<const OpenGLPipeline*>(pipeline);
		if(oglPipeline->m_enableCull) {
			glEnable(GL_CULL_FACE);
			glCullFace(oglPipeline->m_cullFace);
		} else {
			glDisable(GL_CULL_FACE);
		}

		if(oglPipeline->m_enableDepthTest) {
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(oglPipeline->m_depthFunc);
		} else {
			glDisable(GL_DEPTH_TEST);
		}

		glDepthMask(oglPipeline->m_depthWrite);
		glUseProgram(static_cast<const OpenGLShader*>(pipeline->getShader())->m_program);
	}

} // namespace rat
