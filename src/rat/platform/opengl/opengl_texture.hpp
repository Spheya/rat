#pragma once

#include <glad/glad.h>

#include "rat/rendering/interface/texture.hpp"

namespace rat {

	class OpenGLTexture2D : public BaseTexture2D {
		friend class OpenGLGraphicsContext;

	public:
		virtual void setData(const void* data) override;
		virtual void setData(const void* data, unsigned width, unsigned height, TextureFormat format) override;

	protected:
		OpenGLTexture2D();
		~OpenGLTexture2D();

	private:
		GLuint m_texture;
	};

} // namespace rat
