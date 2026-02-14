#include <span>
#include <string>
#include <vector>

#include <rat/core/file_system.hpp>
#include <rat/core/logger.hpp>
#include <rat/core/rat.hpp>
#include <rat/rendering/drawable.hpp>
#include <rat/rendering/graphics.hpp>

int main() {
	rat::printRat();

	rat::FileSystem fileSystem;

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

	std::string vertexShader = fileSystem.loadTextFile(rat::FileSystem::Directory::Assets, "shader.vs");
	std::string fragmentShader = fileSystem.loadTextFile(rat::FileSystem::Directory::Assets, "shader.fs");
	rat::Shader* shader = context->createShader(vertexShader.c_str(), fragmentShader.c_str());
	rat::Pipeline* pipeline = context->createPipeline(shader);

	rat::Mesh* quad = context->createMesh(vertices, indices);

	constexpr unsigned textureData[] = { 0x00000000u, 0xFFFFFFFFu, 0xFFFFFFFFu, 0x00000000u };
	rat::Texture2D* texture = context->createTexture2D(textureData, 2, 2, rat::TextureFormat::RGBA);

	rat::Material material = { .pipeline = pipeline, .texture = texture };
	rat::Drawable drawable = { .mesh = quad, .material = &material, .matrix = glm::mat4(1.0f) };

	while(!context->isCloseRequested()) {
		context->beginFrame();

		context->render(std::span(&drawable, 1));

		context->endFrame();
	}

	context->destroyMesh(quad);
	context->destroyPipeline(pipeline);
	context->destroyShader(shader);
	rat::closeGraphicsContext(context);
}
