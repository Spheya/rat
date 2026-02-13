#pragma once

#include <memory>

#include <glad/glad.h>

#include "rat/core/application_info.hpp"
#include "rat/platform/glfw/glfw_window.hpp"
#include "rat/rendering/interface/graphics_context.hpp"
#include "rat/rendering/material.hpp"

namespace rat {

	class OpenGLGraphicsContext final : public BaseGraphicsContext {
	public:
		OpenGLGraphicsContext(const ApplicationInfo& appInfo);
		~OpenGLGraphicsContext();

		virtual bool isValid() const override;
		virtual bool isCloseRequested() const override;

		virtual void beginFrame() override;
		virtual void endFrame() override;

		virtual Mesh* createMesh(std::span<const Vertex> vertices, std::span<const unsigned> indices) override;
		virtual void destroyMesh(Mesh* mesh) override;

		virtual Shader* createShader(const char* vertex, const char* fragment) override;
		virtual void destroyShader(Shader* shader) override;

		virtual Pipeline* createPipeline(
		    const Shader* shader, CullMode cullMode = CullMode::On, DepthTestMode depthTestMode = DepthTestMode::On, bool depthWriteEnabled = true
		) override;
		virtual void destroyPipeline(Pipeline* pipeline) override;

		virtual void render(std::span<const Drawable> drawables) override;

	private:
		void renderDrawables(std::span<const Drawable> drawables);
		static void bindPipeline(const Pipeline* pipeline);

	private:
		GLFWwindow* m_glContext;
		GLuint m_instanceBuffer;
		std::unique_ptr<glfw::Window> m_window;
	};

} // namespace rat
