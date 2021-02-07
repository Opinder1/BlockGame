 #include "mainmenu.h"

MainMenu::MainMenu() : load_texture(engine::Texture("test.png")), title(load_texture) {
	application->modules.push_back(new CubeScene());
}

MainMenu::~MainMenu() {

}

float r = 0;
void MainMenu::update() {
	application->frame.use();
	application->frame.set_depthtest(false);
	application->frame.set_alphatest(true);
	application->frame.set_culling(engine::Culling::Disabled);

	engine::Sprite::set_material(engine::Sprite::default_material);

	r += 0.01;

	title.set_scale({ 0.2, 0.2 });
	title.set_rotation(r);

	title.draw({ 0, -0.8 });

	title.draw({ 0.2, -0.8 });
	title.draw({ 0.4, -0.8 });
	title.draw({ 0.6, -0.8 });
}