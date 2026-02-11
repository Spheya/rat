#pragma once

#include "glad/glad.h"
#include "rat/rendering/interface/mesh.hpp"

namespace rat {

	class OpenGLMesh final : public BaseMesh {
		friend class OpenGLGraphicsContext;

	public:
		virtual void setVertices(std::span<const Vertex> vertices) override;
		virtual void setIndices(std::span<const unsigned> indices) override;

	protected:
		OpenGLMesh();
		~OpenGLMesh();

	private:
		GLuint m_vao;
		GLuint m_vertexBuffer;
		GLuint m_indexBuffer;
	};

} // namespace rat
