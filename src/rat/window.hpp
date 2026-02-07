#pragma once

#include <string>

#include "surface.hpp"

namespace rat {

	class Window : public Surface {
	public:
		virtual glm::ivec2 getPosition() const = 0;

		virtual const char* getTitle() const = 0;
		virtual void setTitle(const char* title) = 0;
	};

} // namespace rat
