#pragma once

#include <memory>

#include "core.hpp"
#include "math.hpp"

namespace rat {

	class Surface {
	public:
		virtual ~Surface() = default;

		virtual glm::uvec2 getSize() const = 0;
		virtual unsigned getWidth() const { return getSize().x; }
		virtual unsigned getHeight() const { return getSize().y; }

		virtual void swapBuffers() = 0;
	};

	std::unique_ptr<Surface> createSurface(unsigned requestWidth = 960, unsigned requestHeight = 640, const char* title = "rat");
	std::unique_ptr<Surface> createSurface(glm::uvec2 requestSize, const char* title);

} // namespace rat
