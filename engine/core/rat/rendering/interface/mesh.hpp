#pragma once

#include <cstdint>

namespace rat {

	class BaseMesh {
	public:
		BaseMesh(uint32_t numVertices, uint32_t numIndices) : m_numVertices(numVertices), m_numIndices(numIndices) {}
		BaseMesh(BaseMesh&) = delete;
		BaseMesh& operator=(BaseMesh&) = delete;
		BaseMesh(BaseMesh&&) noexcept = delete;
		BaseMesh& operator=(BaseMesh&&) noexcept = delete;
		virtual ~BaseMesh() = default;

	public:
		[[nodiscard]] uint32_t getVertexCount() const { return m_numVertices; }
		[[nodiscard]] uint32_t getIndexCount() const { return m_numIndices; }

	private:
		uint32_t m_numVertices;
		uint32_t m_numIndices;
	};

} // namespace rat
