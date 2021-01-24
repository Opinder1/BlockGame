#include "src/mainmenu/mainmenu.h"

#define debug

int main(int argc, char** argv) {
#ifdef debug
	try {
#endif
		engine::init();

		engine::start(new MainMenu());
#ifdef debug
	}
	catch (const char* error) {
		printf("ERROR: %s\n", error);
	}
#endif
}