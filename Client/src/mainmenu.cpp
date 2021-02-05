 #include "mainmenu.h"

MainMenu::MainMenu() : texture(engine::Texture("test.png")), title(texture) {
}

MainMenu::~MainMenu() {

}

float r = 0;
void MainMenu::update() {
	frame.clear({ 0.0, 0.0, 0.0, 0.0 });
	frame.set_depthtest(false);
	frame.set_alphatest(true);
	frame.set_multisample(true);

	engine::Sprite::set_material(engine::Sprite::default_material);

	r += 0.01;

	title.set_scale({ 0.2, 0.2 });
	title.set_rotation(r);

	title.draw({ 0, -0.8 });

	title.draw({ 0.2, -0.8 });
	title.draw({ 0.4, -0.8 });
	title.draw({ 0.6, -0.8 });
}