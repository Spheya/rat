#pragma once

#include <string>

#include "rendering/render_target.hpp"

namespace rat {

	class Window : public RenderTarget {
	public:
		virtual glm::ivec2 getPosition() const = 0;

		virtual const char* getTitle() const = 0;
		virtual void setTitle(const char* title) = 0;

		virtual bool isCloseRequested() const = 0;
	};

} // namespace rat
