#pragma once

#include "interface/mesh.hpp"
#include "material.hpp"
#include "rat/core/math.hpp"

namespace rat {

	struct Drawable {
		const Mesh* mesh;
		const Material* material;
		glm::mat4 matrix;
	};

} // namespace rat
