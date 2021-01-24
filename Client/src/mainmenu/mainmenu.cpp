 #include "mainmenu.h"

MainMenu::MainMenu() : title("test.png") {
	//application->layers.insert(new CubeScene());
	//application->layers.insert(new Game());

	engine::Sprite::init();
}

MainMenu::~MainMenu() {
	engine::Sprite::deinit();
}

void MainMenu::on_connect() {

}

void MainMenu::on_disconnect() {

}

float r = 0;
void MainMenu::update() {
	engine::Sprite::start_draw();

	r += 0.01;

	title.set_scale({ 0.01, 0.01 });
	for (int x = 0; x < 200; x++) {
		for (int y = 0; y < 200; y++) {
			title.set_position({ 0.01 * x - 1, 0.01 * y - 1 });
			title.draw();
		}
	}
}