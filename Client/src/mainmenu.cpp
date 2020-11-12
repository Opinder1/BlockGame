#include "mainmenu.h"

MainMenu::MainMenu() : texture("test.png"), poly() {
	//client->insert(new Game());
}

MainMenu::~MainMenu() {

}

void MainMenu::on_connect() {

}

void MainMenu::on_disconnect() {

}

void MainMenu::update() {
	texture.use();
	poly.draw();
}