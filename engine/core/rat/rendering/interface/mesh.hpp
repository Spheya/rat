#pragma once

#include <cstdint>

namespace rat {

	class BaseMesh {
	public:
		BaseMesh(uint32_t numVertices, uint32_t numIndices) : numVertices(numVertices), numIndices(numIndices) {}
		BaseMesh(BaseMesh&) = delete;
		BaseMesh& operator=(BaseMesh&) = delete;
		BaseMesh(BaseMesh&&) noexcept = delete;
		BaseMesh& operator=(BaseMesh&&) noexcept = delete;
		virtual ~BaseMesh() = default;

	public:
		[[nodiscard]] uint32_t getVertexCount() const { return numVertices; }
		[[nodiscard]] uint32_t getIndexCount() const { return numIndices; }

	protected:
		uint32_t numVertices;
		uint32_t numIndices;
	};

} // namespace rat
