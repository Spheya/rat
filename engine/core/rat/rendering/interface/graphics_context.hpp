#pragma once

#include <span>

#include "rat/rendering/drawable.hpp"
#include "rat/rendering/graphics_fwd.hpp"

namespace rat {

	struct Vertex;

	class BaseGraphicsContext {
	public:
		BaseGraphicsContext() = default;
		BaseGraphicsContext(BaseGraphicsContext&) = delete;
		BaseGraphicsContext& operator=(BaseGraphicsContext&) = delete;
		BaseGraphicsContext(BaseGraphicsContext&&) = delete;
		BaseGraphicsContext& operator=(BaseGraphicsContext&&) = delete;
		virtual ~BaseGraphicsContext() = default;

	public:
		virtual void beginFrame() = 0;
		virtual void endFrame() = 0;
		virtual void draw(std::span<const Drawable> drawables) = 0;

		virtual Mesh* createMesh(std::span<const Vertex> vertices, std::span<const uint32_t> indices) = 0;
		virtual void destroyMesh(Mesh* mesh) = 0;
	};

} // namespace rat
