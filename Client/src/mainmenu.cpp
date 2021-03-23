 #include "mainmenu.h"

MainMenu::MainMenu() :
	material("sprite"),
	texture(engine::Texture("pixel_test.png"))
{
	//application->modules.push_back(new CubeScene());
	application->modules.push_back(new Game());

	for (int i = 0; i < 3; i++) {
		auto box = std::make_unique<ui::Element>(material, texture, glm::vec2(i * 100, i * 100));
		boxes.push_back(box);
	}
}

MainMenu::~MainMenu() {
}

void MainMenu::update() {
	engine::set_multisample(false);
	engine::set_alphatest(true);
	engine::set_depthtest(false);
	engine::set_culling(engine::Culling::Disabled);

	application->surface.use();

	material.use();
	material.set("surface_size", application->surface.get_size());

	for (auto& box : boxes) {
		box->draw();
	}
}