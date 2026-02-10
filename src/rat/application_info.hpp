#pragma once

#include "math.hpp"

namespace rat {

	struct ApplicationInfo {
		const char* name;
		glm::ivec2 requestedResolution;
		bool fullscreen;
	};

} // namespace rat
