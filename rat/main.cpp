#include <cstring>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <rat/core/editorcontext.hpp>

#include "builder.hpp"
#include "engine.hpp"

int main(int argc, char* argv[]) { // NOLINT(readability-convert-member-functions-to-static)
	if(argc == 2) {
		glfwInit();

		if(!generateBuildFiles(argv[1])) return -1;
		if(!buildEngine(argv[1], true)) return -1;

		Engine engine = linkEngine(argv[1]);
		if(!engine.isValid()) return -1;

		rat::EditorContext ctx{};

		engine.init(&ctx);
		while(true) engine.tick();
		// engine.close();

		// glfwTerminate();
	} else {
		generateBuildFiles(argv[2]);
		if(strcmp(argv[1], "export") == 0) buildEngine(argv[1], false);
	}
}
