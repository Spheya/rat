#pragma once

#include <glm/ext/matrix_float4x4.hpp>

#include "rat/rendering/graphics_fwd.hpp"

namespace rat {

	struct Drawable {
		const Mesh* mesh;
		glm::mat4 matrix;
	};

} // namespace rat
