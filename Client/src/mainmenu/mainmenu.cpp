 #include "mainmenu.h"

MainMenu::MainMenu() : state(1), scene(application->window.get_size()), camera(scene, false)
{
	application->events.event_subscribe(engine::WindowResizeEvent, on_window_resize);

	material = application->shader("shaders\\ui"sv);

	texture._new();

	engine::Texture t = application->texture("textures\\long_test.png"sv);
	texture.set_data(t);

	main_page.emplace_back(new ui::Button([&] {
		state = 0;
		//application->modules.emplace_back(new Game());
	}, texture, { 0, 0 }, t.get_size()));

	main_page.emplace_back(new ui::Button([&] {

	}, texture, { 150, 0 }, t.get_size()));

	main_page.emplace_back(new ui::Button([&] {
		application->running = false;
	}, texture, { 300, 0 }, t.get_size()));
}

MainMenu::~MainMenu() {
	material._delete();
	texture._delete();
}

void MainMenu::on_window_resize(const engine::WindowResizeEvent* e) {
	camera.set_size(e->size);
}

void MainMenu::update() {
	engine::set_multisample(false);
	engine::set_alphatest(true);
	engine::set_depthtest(false);
	engine::set_culling(engine::CullingMode::Disabled);

	camera.use();

	switch (state) {
	case 0:
		break;

	case 1:
		material.use();

		for (auto& item : main_page) {
			item->draw(material);
		}

		break;
	}

	application->window.use();

	application->window_program.use();

	scene.get_texture().use(0);

	engine::Renderer2D::draw_quad();
}