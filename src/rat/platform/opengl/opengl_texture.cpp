#include "opengl_texture.hpp"

namespace rat {

	static GLenum asOpenGLFormat(TextureFormat) {
		return GL_RGBA;
	}

	static GLenum asOpenGLInternalFormat(TextureFormat) {
		return GL_RGBA;
	}

	OpenGLTexture2D::OpenGLTexture2D() : m_texture(0) {
		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	OpenGLTexture2D::~OpenGLTexture2D() {
		glDeleteTextures(1, &m_texture);
	}

	void OpenGLTexture2D::setData(const void* data) {
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, asOpenGLFormat(m_format), GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::setData(const void* data, unsigned width, unsigned height, TextureFormat format) {
		m_width = width;
		m_height = height;
		m_format = format;
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, asOpenGLInternalFormat(m_format), m_width, m_height, 0, asOpenGLFormat(format), GL_UNSIGNED_BYTE, data);
	}

} // namespace rat
