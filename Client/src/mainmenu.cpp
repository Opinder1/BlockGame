 #include "mainmenu.h"

MainMenu::MainMenu() : material("texture"), poly(&material) {
	application->layers.insert(new CubeScene());
	application->layers.insert(new Game());
}

MainMenu::~MainMenu() {

}

void MainMenu::on_connect() {

}

void MainMenu::on_disconnect() {

}

void MainMenu::update() {

}