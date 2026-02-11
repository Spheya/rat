#pragma once

#include "rat/core/math.hpp"

namespace rat {

	class RenderTarget {
	public:
		virtual ~RenderTarget() = default;

		virtual glm::uvec2 getSize() const = 0;
		virtual unsigned getWidth() const { return getSize().x; }
		virtual unsigned getHeight() const { return getSize().y; }
	};

} // namespace rat
