#include "opengl_mesh.hpp"
#include "rat/rendering/vertex.hpp"

namespace rat {

	OpenGLMesh::OpenGLMesh(GLuint instanceBuffer) : m_vao(0), m_vertexBuffer(0), m_indexBuffer(0) {
		numVertices = 0;
		numIndices = 0;
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(2, &m_vertexBuffer);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);  // NOLINT
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12); // NOLINT
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)24); // NOLINT
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32); // NOLINT
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)48); // NOLINT
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);

		glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0 * sizeof(float)));  // NOLINT
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(4 * sizeof(float)));  // NOLINT
		glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(8 * sizeof(float)));  // NOLINT
		glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(12 * sizeof(float))); // NOLINT
		glEnableVertexAttribArray(5);
		glEnableVertexAttribArray(6);
		glEnableVertexAttribArray(7);
		glEnableVertexAttribArray(8);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);
		glVertexAttribDivisor(7, 1);
		glVertexAttribDivisor(8, 1);

		glBindVertexArray(0);
	}

	OpenGLMesh::~OpenGLMesh() {
		glDeleteBuffers(2, &m_vertexBuffer);
		glDeleteVertexArrays(1, &m_vao);
	}

	void OpenGLMesh::setVertices(std::span<const Vertex> vertices) {
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		if(vertices.size() == numVertices) {
			glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		} else {
			numVertices = unsigned(vertices.size());
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
		}
	}

	void OpenGLMesh::setIndices(std::span<const unsigned> indices) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
		if(indices.size() == numIndices) {
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(unsigned), indices.data());
		} else {
			numIndices = unsigned(indices.size());
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), GL_STATIC_DRAW);
		}
	}

} // namespace rat
