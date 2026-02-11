#pragma once

#include "rat/math.hpp"

namespace rat {

	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uv;
		glm::vec4 color;
		glm::vec4 tangent;
	};

} // namespace rat
