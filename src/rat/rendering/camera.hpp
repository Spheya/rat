#pragma once

#include <glm/glm.hpp>

namespace rat {

	struct Camera {
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
	};

} // namespace rat
