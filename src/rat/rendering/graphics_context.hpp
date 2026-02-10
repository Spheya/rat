#pragma once

#include "rat/application_info.hpp"
#include "render_target.hpp"

namespace rat {

	enum class GraphicsBackend { None, OpenGL3, Vulkan };

	class GraphicsContext {
	public:
		explicit GraphicsContext(GraphicsBackend graphicsBackend) : m_graphicsBackend(graphicsBackend) {}
		virtual ~GraphicsContext() = default;

		virtual bool isValid() const = 0;
		virtual bool isCloseRequested() const = 0;

		virtual void beginFrame() = 0;
		virtual void endFrame() = 0;

		GraphicsBackend getGraphicsBackend() const { return m_graphicsBackend; }
		RenderTarget& getMainRenderTarget() const { return *renderTarget; }

	protected:
		RenderTarget* renderTarget;

	private:
		GraphicsBackend m_graphicsBackend;
	};

	GraphicsContext* createGraphicsContext(const ApplicationInfo& appInfo, GraphicsBackend requestedBackend = GraphicsBackend::None);
	void closeGraphicsContext(GraphicsContext* context);

} // namespace rat
