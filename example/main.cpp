#include <rat/core.hpp>
#include <rat/surface.hpp>

int main() {
	rat::intialize();
	{
		std::unique_ptr<rat::Surface> surface = rat::createSurface();
		while(true) {
			rat::pollEvents();
			surface->swapBuffers();
		}
	}
	rat::terminate();
	return 0;
}
