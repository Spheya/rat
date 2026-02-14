#pragma once

#include <span>

#include "mesh.hpp"
#include "pipeline.hpp"
#include "rat/rendering/drawable.hpp"
#include "rat/rendering/render_target.hpp"
#include "rat/rendering/vertex.hpp"
#include "shader.hpp"
#include "texture.hpp"

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

		virtual Shader* createShader(const char* vertex, const char* fragment) = 0;
		virtual void destroyShader(Shader* shader) = 0;

		virtual Pipeline* createPipeline(
		    const Shader* shader, CullMode cullMode = CullMode::On, DepthTestMode depthTestMode = DepthTestMode::On, bool depthWriteEnabled = true
		) = 0;
		virtual void destroyPipeline(Pipeline* pipeline) = 0;

		virtual Texture2D* createTexture2D(const void* data, unsigned width, unsigned height, TextureFormat format) = 0;
		virtual void destroyTexture2D(Texture2D* texture) = 0;

		virtual void render(std::span<const Drawable> drawables) = 0;

		GraphicsBackend getGraphicsBackend() const { return m_graphicsBackend; }
		RenderTarget& getMainRenderTarget() const { return *renderTarget; }

	protected:
		RenderTarget* renderTarget;

	private:
		GraphicsBackend m_graphicsBackend;
	};

	using GraphicsContext = BaseGraphicsContext;

} // namespace rat
