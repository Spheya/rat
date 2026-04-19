#include "opengl_mesh.hpp"

#include <cassert>
#include <cstddef>
#include <limits>

namespace rat::opengl {

	Mesh::Mesh(std::span<const Vertex> vertices, std::span<const uint32_t> indices) :
	    BaseMesh(uint32_t(vertices.size()), uint32_t(indices.size())), m_vao(0), m_vertexBuffer(0), m_indexBuffer(0) {
		assert(vertices.size() <= std::numeric_limits<uint32_t>::max());
		assert(indices.size() <= std::numeric_limits<uint32_t>::max());

		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);
		glGenBuffers(2, &m_vertexBuffer);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, GLsizeiptr(indices.size() * sizeof(uint32_t)), indices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(vertices.size() * sizeof(Vertex)), vertices.data(), GL_STATIC_DRAW);

		// NOLINTBEGIN (performance-no-int-to-ptr): OpenGL needs us to do that
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, uv)));
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, tangent)));
		// NOLINTEND

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);

		glBindVertexArray(0);
	}

	Mesh::~Mesh() {
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(2, &m_vertexBuffer);
	}

} // namespace rat::opengl
