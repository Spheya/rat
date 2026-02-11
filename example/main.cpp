#include <vector>

#include <rat/core/logger.hpp>
#include <rat/core/rat.hpp>
#include <rat/rendering/drawable.hpp>
#include <rat/rendering/graphics.hpp>

int main() {
	rat::printRat();

	rat::ApplicationInfo appInfo = {};
	appInfo.name = "Rat";
	appInfo.requestedResolution = glm::ivec2(960, 640);
	appInfo.fullscreen = false;

	rat::BaseGraphicsContext* context = rat::createGraphicsContext(appInfo);

	const std::vector<rat::Vertex> vertices = {
		{ .position = { -0.5f, -0.5f, 0.0f }, .normal = { 0, 0, 1 }, .uv = { 0, 0 }, .color = { 1, 1, 1, 1 }, .tangent = { 1, 0, 0, 1 } },
		{ .position = { +0.5f, -0.5f, 0.0f }, .normal = { 0, 0, 1 }, .uv = { 1, 0 }, .color = { 1, 1, 1, 1 }, .tangent = { 1, 0, 0, 1 } },
		{ .position = { +0.5f, +0.5f, 0.0f }, .normal = { 0, 0, 1 }, .uv = { 1, 1 }, .color = { 1, 1, 1, 1 }, .tangent = { 1, 0, 0, 1 } },
		{ .position = { -0.5f, +0.5f, 0.0f }, .normal = { 0, 0, 1 }, .uv = { 0, 1 }, .color = { 1, 1, 1, 1 }, .tangent = { 1, 0, 0, 1 } },
	};
	const std::vector<unsigned> indices = { 0, 1, 2, 0, 2, 3 };

	rat::Mesh* quad = context->createMesh(vertices, indices);
	rat::Drawable drawable = { quad };

	rat::info("test");

	while(!context->isCloseRequested()) {
		context->beginFrame();

		context->render(&drawable, 1);

		context->endFrame();
	}

	context->destroyMesh(quad);
	rat::closeGraphicsContext(context);
}
