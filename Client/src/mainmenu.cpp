 #include "mainmenu.h"

MainMenu::MainMenu() : material(), poly() {
	//client->insert(new Game());
}

MainMenu::~MainMenu() {

}

void MainMenu::on_connect() {

}

void MainMenu::on_disconnect() {

}

void MainMenu::update() {
	material.use();
	poly.draw();
}