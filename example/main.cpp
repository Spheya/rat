#include <rat/rat.hpp>
#include <rat/rendering/graphics_context.hpp>

int main() {
	rat::printRat();

	rat::ApplicationInfo appInfo = {};
	appInfo.name = "Rat";
	appInfo.requestedResolution = glm::ivec2(960, 640);
	appInfo.fullscreen = false;

	rat::GraphicsContext* context = rat::createGraphicsContext(appInfo);

	while(!context->isCloseRequested()) {
		context->beginFrame();

		context->endFrame();
	}

	rat::closeGraphicsContext(context);
}
