#include <cstring>

#include <GLFW/glfw3.h>

#include "builder.hpp"

int main(int argc, char* argv[]) {
	if(argc == 2) {
		glfwInit();

		if(!generateBuildFiles(argv[1])) return -1;
		if(!buildEngine(argv[1], true)) return -1;
		if(!linkEngine(argv[1])) return -1;

		glfwTerminate();
	} else {
		generateBuildFiles(argv[2]);
		if(strcmp(argv[1], "export") == 0) buildEngine(argv[1], false);
	}
}
