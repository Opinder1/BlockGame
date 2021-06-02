 #include "mainmenu.h"

MainMenu::MainMenu() :
	state(1),
	scene(application->window.get_size()),
	camera(scene)
{
	application->events.event_subscribe(engine::WindowResizeEvent, on_window_resize);

	material = application->shader("blockgame\\shaders\\ui\\ui.json"s);

	texture._new();
	engine::Texture t("blockgame\\textures\\default.png"s);
	texture.set_data(t);

	main_page.emplace_back(new ui::Button([=] {
		state = 0;
		//application->modules.emplace_back(new Game());
	}, material, texture, { 0, 0 }, t.get_size()));

	main_page.emplace_back(new ui::Button([=] {

	}, material, texture, { 150, 0 }, t.get_size()));

	main_page.emplace_back(new ui::Button([=] {
		application->running = false;
	}, material, texture, { 300, 0 }, t.get_size()));
}

MainMenu::~MainMenu() {
	material._delete();
	texture._delete();
}

void MainMenu::on_window_resize(const engine::WindowResizeEvent* e) {
	scene.set_size(e->size);
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
		material.set<glm::uvec2>("surface_size", application->window.get_size());

		for (auto& item : main_page) {
			item->draw();
		}

		break;
	}

	// TODO Dont have this here
	application->surface.use();

	material.use();

	scene.get_texture().use(0);

	material.set("pos", glm::vec2{ 0, 0 });

	material.set("rot", 0.0f);

	material.set("scale", glm::vec2{ 1, 1 });

	engine::Renderer2D::draw_quad();
}