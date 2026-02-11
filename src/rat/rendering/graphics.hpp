#pragma once

#include "interface/graphics_context.hpp"
#include "rat/core/application_info.hpp"

namespace rat {

	GraphicsContext* createGraphicsContext(const ApplicationInfo& appInfo, GraphicsBackend requestedBackend = GraphicsBackend::None);
	void closeGraphicsContext(GraphicsContext* context);

} // namespace rat
