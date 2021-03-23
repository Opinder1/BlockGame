#include "src/application.h"

#include "src/mainmenu.h"

int main(int argc, char** argv) {
	//try {
		application = new Application();

		application->modules.push_back(new MainMenu());

		application->run();

		delete application;
	//}
	//catch (const char* error) {
	//	printf("ERROR: %s\n", error);
	//}
}