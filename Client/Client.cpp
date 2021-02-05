#include "src/application.h"

#include "src/cubescene.h"
#include "src/mainmenu.h"

int main(int argc, char** argv) {
	try {
		application = new Application();

		application->layers.push_back(new CubeScene());
		application->layers.push_back(new MainMenu());

		application->run();

		delete application;
	}
	catch (const char* error) {
		printf("(try) ERROR: %s\n", error);
	}
}