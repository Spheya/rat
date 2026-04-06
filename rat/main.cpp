#include "builder.hpp"
#include "rat/editor/editor.hpp"

int main(int argc, char* argv[]) {
	if(argc == 2) {
		runEditor();

		buildEngine(argv[1], true);
		linkEngine(argv[1]);
	} else {
		buildEngine(argv[2], false);
	}
}
