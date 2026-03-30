#pragma once

#include <glm/glm.hpp>

namespace rat {

	class RenderTarget {
	public:
		RenderTarget() = default;
		RenderTarget(const RenderTarget&) = default;
		RenderTarget& operator=(const RenderTarget&) = default;
		RenderTarget(RenderTarget&&) = default;
		RenderTarget& operator=(RenderTarget&&) = default;
		virtual ~RenderTarget() = default;

		[[nodiscard]] virtual glm::uvec2 getSize() const = 0;
		[[nodiscard]] unsigned getWidth() const { return getSize().x; }
		[[nodiscard]] unsigned getHeight() const { return getSize().y; }
	};

} // namespace rat
