#include "src/client.h"

#include "src/mainmenu.h"

int main(int argc, char** argv) {
	client_init();

	client_run(new MainMenu());
}