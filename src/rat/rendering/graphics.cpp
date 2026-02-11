#include "graphics.hpp"
#include "rat/platform/opengl/opengl_graphics_context.hpp"

namespace rat {

	GraphicsContext* createGraphicsContext(const ApplicationInfo& appInfo, GraphicsBackend) {
		return new OpenGLGraphicsContext(appInfo);
	}

	void closeGraphicsContext(GraphicsContext* context) {
		delete context;
	}

} // namespace rat
