#pragma once

#ifdef RAT_OPENGL
namespace rat::opengl {
	class GraphicsContext;
	class Mesh;
} // namespace rat::opengl
#endif

namespace rat {
	using GraphicsContext = opengl::GraphicsContext;
	using Mesh = opengl::Mesh;
} // namespace rat
