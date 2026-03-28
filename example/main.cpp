#include <rat/core/rat.hpp>
#include <rat/loader/mesh_loader.hpp>
#include <rat/rendering/drawable.hpp>

#include "rat/core/logger.hpp"

int main() {
	rat::printRat();

	rat::log("hi");
	rat::warn("hi");
	rat::error("hi");
}
