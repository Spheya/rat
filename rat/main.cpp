#include <cstring>

#include "builder.hpp"
#include "rat/editor/editor.hpp"

int main(int argc, char* argv[]) {
	if(argc == 2) {
		runEditor();
		generateBuildFiles(argv[1]);
		buildEngine(argv[1], true);
		linkEngine(argv[1]);
	} else {
		generateBuildFiles(argv[2]);
		if(strcmp(argv[1], "export") == 0) buildEngine(argv[1], false);
	}
}
