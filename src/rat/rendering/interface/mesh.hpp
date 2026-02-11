#pragma once

#include <span>

#include "rat/rendering/vertex.hpp"

namespace rat {

	class BaseMesh {
	public:
		virtual void setVertices(std::span<const Vertex> vertices) = 0;
		virtual void setIndices(std::span<const unsigned> indices) = 0;

		unsigned vertexCount() const noexcept { return numVertices; }
		unsigned indexCount() const noexcept { return numIndices; }

	protected:
		virtual ~BaseMesh() = default;

	protected:
		unsigned numVertices;
		unsigned numIndices;
	};

	using Mesh = BaseMesh;

} // namespace rat
