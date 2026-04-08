#include <cstring>

#include <glfw/glfw3.h>

#include "builder.hpp"

int main(int argc, char* argv[]) {
	if(argc == 2) {
		generateBuildFiles(argv[1]);
		buildEngine(argv[1], true);

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		GLFWwindow* window = glfwCreateWindow(640, 480, "Rat Editor", nullptr, nullptr);
		glfwMakeContextCurrent(window);

		linkEngine(argv[1]);

		while(!glfwWindowShouldClose(window)) {
			glfwPollEvents();
			glfwSwapBuffers(window);
		}
	} else {
		generateBuildFiles(argv[2]);
		if(strcmp(argv[1], "export") == 0) buildEngine(argv[1], false);
	}
}
