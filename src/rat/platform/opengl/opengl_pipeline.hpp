#pragma once

#include <glad/glad.h>

#include "rat/rendering/interface/pipeline.hpp"

namespace rat {

	class OpenGLPipeline final : public BasePipeline {
		friend class OpenGLGraphicsContext;

	protected:
		OpenGLPipeline(const Shader* shader, CullMode cullMode, DepthTestMode depthTestMode, bool depthWriteEnabled);
		~OpenGLPipeline() = default;

	private:
		bool m_enableCull;
		bool m_enableDepthTest;
		GLenum m_cullFace;
		GLenum m_depthFunc;
		GLboolean m_depthWrite;
	};

} // namespace rat
