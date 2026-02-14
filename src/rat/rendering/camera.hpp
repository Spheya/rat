#pragma once

#include "rat/core/math.hpp"

namespace rat {

	struct Camera {
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
	};

} // namespace rat
