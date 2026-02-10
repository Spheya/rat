#include "graphics_context.hpp"
#include "rat/platform/opengl/opengl_graphics_context.hpp"

namespace rat {

	GraphicsContext* createGraphicsContext(const ApplicationInfo& appInfo, GraphicsBackend) {
		return new opengl::GraphicsContext(appInfo);
	}

	void closeGraphicsContext(GraphicsContext* context) {
		delete context;
	}

} // namespace rat
