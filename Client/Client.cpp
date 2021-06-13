#include "src/application.h"

#include "src/mainmenu/mainmenu.h"

int main(int argc, char** argv) {
	application = new BlockGameApplication();

	application->new_module<MainMenu>();

	application->run();

	delete application;
}