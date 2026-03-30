#include <rat/core/rat.hpp>
#include <rat/loader/mesh_loader.hpp>
#include <rat/rendering/drawable.hpp>

#include "rat/core/logger.hpp"

int main() {
	rat::printRat();

	glm::vec3 v(1.0f, 2.53f, -8.0f);

	rat::log("{}", v);
	rat::warn("hi");
	rat::error("hi");
}
