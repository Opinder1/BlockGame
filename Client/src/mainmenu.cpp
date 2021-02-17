 #include "mainmenu.h"

MainMenu::MainMenu() : title(engine::Texture("pixel_test.png")), material("sprite") {
	//application->modules.push_back(new CubeScene());
	application->modules.push_back(new Game());
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

	title.use(0);
	material.set("texture_size", title.get_size());

	material.set<glm::vec2>("scale", { 1, 1 });

	for (int i = 0; i < 3; i++) {
		material.set<glm::vec2>("pos", { title.get_size() * i });
		engine::QuadRenderer::draw();
	}
}