#pragma once

#include <memory>

#include "rat/platform/glfw/glfw_window.hpp"
#include "rat/rendering/graphics_context.hpp"

namespace rat::opengl {

	class GraphicsContext final : public rat::GraphicsContext {
	public:
		GraphicsContext(const ApplicationInfo& appInfo);
		~GraphicsContext();

		virtual bool isValid() const override;
		virtual bool isCloseRequested() const override;

		virtual void beginFrame() override;
		virtual void endFrame() override;

	private:
		GLFWwindow* m_glContext;
		std::unique_ptr<glfw::Window> m_window;
	};

} // namespace rat::opengl
