#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <rat/core/rat.hpp>
#include <rat/loader/mesh_loader.hpp>
#include <rat/rendering/drawable.hpp>

#include "rat/core/logger.hpp"

int main() {
	rat::printRat();

	glm::vec3 v(1.0f, 2.53f, -8.0f);
	glm::mat3 m(v, v, v);
	auto q = glm::identity<glm::quat>();

	rat::log("{}", v);
	rat::warn("{}", m);
	rat::error("{}", q);
}
