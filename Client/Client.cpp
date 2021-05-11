#include "src/application.h"

#include "src/mainmenu.h"

int main(int argc, char** argv) {
	application = new BlockGameApplication();

	application->modules.emplace_back(new MainMenu());

	application->run();

	delete application;
}