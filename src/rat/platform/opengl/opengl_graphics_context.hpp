#pragma once

#include <memory>

#include "rat/application_info.hpp"
#include "rat/platform/glfw/glfw_window.hpp"
#include "rat/rendering/interface/graphics_context.hpp"

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

		virtual void render(const Drawable* drawables, unsigned drawableCount) override;

	private:
		GLFWwindow* m_glContext;
		std::unique_ptr<glfw::Window> m_window;
	};

} // namespace rat
