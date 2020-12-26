#include "src/mainmenu.h"

int main(int argc, char** argv) {
	try {
		engine::init();

		engine::start(new MainMenu());
	}
	catch (const char* error) {
		printf("ERROR: %s\n", error);
	}

}