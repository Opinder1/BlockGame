 #include "mainmenu.h"

MainMenu::MainMenu() : texture(engine::Texture("test.png")), title(texture) {
	application->layers.push_back(new CubeScene());
	//application->layers.insert(new Game());
}

MainMenu::~MainMenu() {

}

float r = 0;
void MainMenu::update() {
	engine::FrameBuffer::clear({ 1.0, 1.0, 1.0, 0.0 });
	engine::FrameBuffer::set_depthtest(false);
	engine::FrameBuffer::set_alphatest(true);
	engine::FrameBuffer::set_multisample(true);

	engine::Sprite::set_material(engine::default_sprite_material);

	r += 0.01;

	title.set_scale({ 0.2, 0.2 });
	title.set_rotation(r);

	title.draw({ 0, -0.8 });

	title.draw({ 0.2, -0.8 });
	title.draw({ 0.4, -0.8 });
	title.draw({ 0.6, -0.8 });
}