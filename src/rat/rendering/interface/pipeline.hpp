#pragma once

#include "shader.hpp"

namespace rat {

	enum class CullMode { Back, Front, Off, On = Back };
	enum class DepthTestMode { LessThan, LessThanEqual, GreaterThan, GreaterThanEqual, Equal, NotEqual, Always, On = LessThan, Off = Always };

	class BasePipeline {
	public:
		const Shader* getShader() const noexcept { return m_shader; }
		CullMode getCullMode() const noexcept { return m_cullMode; }
		DepthTestMode getDepthTestMode() const noexcept { return m_depthTestMode; }
		bool isDepthWriteEnabled() const noexcept { return m_enableDepthWrite; }

	protected:
		BasePipeline(const Shader* shader, CullMode cullMode, DepthTestMode depthTestMode, bool enableDepthWrite) :
		    m_shader(shader), m_cullMode(cullMode), m_depthTestMode(depthTestMode), m_enableDepthWrite(enableDepthWrite) {}
		virtual ~BasePipeline() = default;

	private:
		const Shader* m_shader;
		CullMode m_cullMode;
		DepthTestMode m_depthTestMode;
		bool m_enableDepthWrite;
	};

	using Pipeline = BasePipeline;

} // namespace rat
