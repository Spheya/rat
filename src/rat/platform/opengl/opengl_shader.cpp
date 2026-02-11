#include "opengl_shader.hpp"

#include <string>

#include "rat/core/logger.hpp"

namespace rat {

	static GLuint loadShader(const char* src, GLenum type) {
		GLuint result = glCreateShader(type);
		glShaderSource(result, 1, &src, nullptr);
		glCompileShader(result);

#ifndef RAT_STRIP_LOGGER
		int success;
		glGetShaderiv(result, GL_COMPILE_STATUS, &success);
		if(!success) {
			GLint logLength = 0;
			glGetShaderiv(result, GL_INFO_LOG_LENGTH, &logLength);
			std::string log(logLength, 0);
			glGetShaderInfoLog(result, logLength, nullptr, log.data());
			rat::error("Shader compilation error: {}", log);
		}
#endif

		return result;
	}

	OpenGLShader::OpenGLShader(const char* vertexShader, const char* fragmentShader) : m_program(glCreateProgram()) {
		GLuint vsh = loadShader(vertexShader, GL_VERTEX_SHADER);
		GLuint fsh = loadShader(fragmentShader, GL_FRAGMENT_SHADER);

		glAttachShader(m_program, vsh);
		glAttachShader(m_program, fsh);
		glLinkProgram(m_program);

#ifndef RAT_STRIP_LOGGER
		int success;
		glGetProgramiv(m_program, GL_LINK_STATUS, &success);
		if(!success) {
			GLint logLength = 0;
			glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logLength);
			std::string log(logLength, 0);
			glGetProgramInfoLog(m_program, logLength, nullptr, log.data());
			rat::error("Shader linking error: {}", log);
		}

		glValidateProgram(m_program);

		glGetProgramiv(m_program, GL_VALIDATE_STATUS, &success);
		if(!success) {
			GLint logLength = 0;
			glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logLength);
			std::string log(logLength, 0);
			glGetProgramInfoLog(m_program, logLength, nullptr, log.data());
			rat::error("Shader validation error: {}", log);
		}
#endif

		glDeleteShader(vsh);
		glDeleteShader(fsh);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_program);
	}

} // namespace rat
