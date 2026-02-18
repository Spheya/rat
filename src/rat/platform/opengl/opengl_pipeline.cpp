#include "opengl_pipeline.hpp"

namespace rat {

	OpenGLPipeline::OpenGLPipeline(const Shader* shader, CullMode cullMode, DepthTestMode depthTestMode, bool depthWriteEnabled) :
	    BasePipeline(shader, cullMode, depthTestMode, depthWriteEnabled), m_enableCull(false), m_enableDepthTest(false) {
		if(cullMode != CullMode::Off) {
			m_enableCull = true;
			m_cullFace = cullMode == CullMode::Back ? GL_BACK : GL_FRONT;
		}

		if(depthTestMode != DepthTestMode::Off) {
			m_enableDepthTest = true;
			switch(depthTestMode) {
			case DepthTestMode::LessThan: m_depthFunc = GL_LESS; break;
			case DepthTestMode::LessThanEqual: m_depthFunc = GL_LEQUAL; break;
			case DepthTestMode::GreaterThan: m_depthFunc = GL_GREATER; break;
			case DepthTestMode::GreaterThanEqual: m_depthFunc = GL_GEQUAL; break;
			case DepthTestMode::Equal: m_depthFunc = GL_EQUAL; break;
			case DepthTestMode::NotEqual: m_depthFunc = GL_NOTEQUAL; break;
			case DepthTestMode::Always: m_depthFunc = GL_ALWAYS; break;
			}
		}

		m_depthWrite = depthWriteEnabled ? GL_TRUE : GL_FALSE;
	}

} // namespace rat
