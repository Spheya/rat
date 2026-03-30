#pragma once

#include <glm/glm.hpp>

namespace rat {

	struct ApplicationInfo {
		const char* name;
		glm::ivec2 requestedResolution;
		bool fullscreen;
	};

} // namespace rat
