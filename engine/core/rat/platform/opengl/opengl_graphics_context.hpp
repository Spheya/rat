#pragma once

#include "rat/rendering/interface/graphics_context.hpp"

struct GLFWwindow;

namespace rat {
	struct EditorContext;
}

namespace rat::opengl {

	class GraphicsContext final : public BaseGraphicsContext {
	public:
		GraphicsContext(EditorContext* editorContext);
		GraphicsContext(GraphicsContext&) = delete;
		GraphicsContext& operator=(GraphicsContext&) = delete;
		GraphicsContext(GraphicsContext&&) = delete;
		GraphicsContext& operator=(GraphicsContext&&) = delete;
		~GraphicsContext() override;

	public:
		Mesh* createMesh(std::span<const Vertex> vertices, std::span<const uint32_t> indices) override;
		void destroyMesh(Mesh* mesh) override;

	private:
		GLFWwindow* m_window;
	};

} // namespace rat::opengl
