#include "src/client.h"

#include "src/mainmenu.h"

int main(int argc, char** argv) {
	client_init();

	client->window.set_icon(engine::Texture("icon.png"));

	client_run(new MainMenu());
}