#pragma once

#include "mesh.hpp"
#include "rat/rendering/drawable.hpp"
#include "rat/rendering/render_target.hpp"
#include "rat/rendering/vertex.hpp"

namespace rat {

	enum class GraphicsBackend { None, OpenGL3, Vulkan };

	class BaseGraphicsContext {
	public:
		explicit BaseGraphicsContext(GraphicsBackend graphicsBackend) : m_graphicsBackend(graphicsBackend) {}
		virtual ~BaseGraphicsContext() = default;

		virtual bool isValid() const = 0;
		virtual bool isCloseRequested() const = 0;

		virtual void beginFrame() = 0;
		virtual void endFrame() = 0;

		virtual Mesh* createMesh(std::span<const Vertex> vertices, std::span<const unsigned> indices) = 0;
		virtual void destroyMesh(Mesh* mesh) = 0;

		virtual void render(const Drawable* drawables, unsigned drawableCount) = 0;

		GraphicsBackend getGraphicsBackend() const { return m_graphicsBackend; }
		RenderTarget& getMainRenderTarget() const { return *renderTarget; }

	protected:
		RenderTarget* renderTarget;

	private:
		GraphicsBackend m_graphicsBackend;
	};

	using GraphicsContext = BaseGraphicsContext;

} // namespace rat
