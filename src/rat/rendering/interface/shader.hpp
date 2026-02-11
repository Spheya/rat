#pragma once

namespace rat {

	class BaseShader {
	protected:
		virtual ~BaseShader() = default;
	};

	using Shader = BaseShader;

} // namespace rat
