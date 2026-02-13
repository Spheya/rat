#pragma once

#include <glad/glad.h>

#include "rat/rendering/interface/shader.hpp"

namespace rat {

	class OpenGLShader final : public BaseShader {
		friend class OpenGLGraphicsContext;

	protected:
		OpenGLShader(const char* vertexShader, const char* fragmentShader);
		~OpenGLShader();

	protected:
		GLuint m_program;
	};

} // namespace rat
