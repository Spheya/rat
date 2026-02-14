#pragma once

#include "interface/pipeline.hpp"
#include "interface/texture.hpp"

namespace rat {

	struct Material {
		const Pipeline* pipeline;
		const Texture2D* texture;
	};

} // namespace rat
