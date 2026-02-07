#include <rat/core.hpp>
#include <rat/surface.hpp>

int main() {
	rat::intialize();
	{
		std::unique_ptr<rat::Surface> surface = rat::createSurface(); // NOLINT
		while(true) { rat::pollEvents(); }
	}
	rat::terminate();
	return 0;
}
