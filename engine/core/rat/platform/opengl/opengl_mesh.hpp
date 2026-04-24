#pragma once

#include <span>

#include <glad/gl.h>

#include "rat/rendering/graphics_fwd.hpp"
#include "rat/rendering/interface/mesh.hpp"
#include "rat/rendering/vertex.hpp"

namespace rat::opengl {

	class Mesh final : public BaseMesh {
		friend class rat::opengl::GraphicsContext;

	public:
		Mesh(Mesh&) = delete;
		Mesh& operator=(Mesh&) = delete;
		Mesh(Mesh&&) = delete;
		Mesh& operator=(Mesh&&) = delete;

	private:
		Mesh(std::span<const Vertex> vertices, std::span<const uint32_t> indices);
		~Mesh() override;

	private:
		[[nodiscard]] GLuint getVao() const { return m_vao; }

	private:
		GLuint m_vao;
		GLuint m_vertexBuffer;
		GLuint m_indexBuffer;
	};

} // namespace rat::opengl
