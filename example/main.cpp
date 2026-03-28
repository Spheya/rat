#include <imgui.h>
#include <rat/core/rat.hpp>
#include <rat/loader/mesh_loader.hpp>
#include <rat/rendering/drawable.hpp>
#include <rat/rendering/graphics.hpp>

#include "rat/core/logger.hpp"

int main() {
	rat::printRat();

	rat::ApplicationInfo appInfo = {};
	appInfo.name = "Rat";
	appInfo.requestedResolution = glm::ivec2(960, 640);
	appInfo.fullscreen = false;

	rat::BaseGraphicsContext* context = rat::createGraphicsContext(appInfo);

	rat::log("hi");
	rat::warn("hi");
	rat::error("hi");

	rat::closeGraphicsContext(context);
}
