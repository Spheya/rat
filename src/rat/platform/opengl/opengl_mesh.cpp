#include "opengl_mesh.hpp"
#include "rat/rendering/vertex.hpp"

namespace rat {

	OpenGLMesh::OpenGLMesh() : m_vao(0), m_vertexBuffer(0), m_indexBuffer(0) {
		numVertices = 0;
		numIndices = 0;
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(2, &m_vertexBuffer);

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

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
			numVertices = vertices.size();
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
		}
	}

	void OpenGLMesh::setIndices(std::span<const unsigned> indices) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
		if(indices.size() == numIndices) {
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(unsigned), indices.data());
		} else {
			numIndices = indices.size();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), GL_STATIC_DRAW);
		}
	}

} // namespace rat
