#pragma once

#include <glm/glm.hpp>

#include "interface/mesh.hpp"
#include "material.hpp"

namespace rat {

	struct Drawable {
		const Mesh* mesh;
		const Material* material;
		glm::mat4 matrix;
	};

} // namespace rat
