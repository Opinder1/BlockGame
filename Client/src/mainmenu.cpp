 #include "mainmenu.h"

MainMenu::MainMenu() :
	material(new engine::Material("sprite")),
	texture(new engine::TextureBuffer(engine::Texture("pixel_test"))),
	state(1)
{
	main_page.emplace_back(new ui::Button([=] {
		state = 0;
		application->modules.emplace_back(new Game());
	}, material, texture, { 100, 100 }));

	main_page.emplace_back(new ui::Button([=] {

	}, material, texture, { 250, 100 }));

	main_page.emplace_back(new ui::Button([=] {
		application->running = false;
	}, material, texture, { 400, 100 }));
}

MainMenu::~MainMenu() {

}

void MainMenu::update() {
	engine::set_multisample(false);
	engine::set_alphatest(true);
	engine::set_depthtest(false);
	engine::set_culling(engine::Culling::Disabled);

	application->surface.use();

	switch (state) {
	case 0:
		break;

	case 1:
		material->use();
		material->set("surface_size", application->surface.get_size());

		for (auto& item : main_page) {
			item->draw();
		}

		break;
	}
}