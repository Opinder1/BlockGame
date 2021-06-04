#include "ui.h"

namespace ui {
	Element::Element(engine::Texture2D& texture, glm::vec2 position, glm::vec2 size) :
		texture(texture),
		engine::Transform2D{ position, 0, size },
		size(size),
		model(1)
	{

	}

	Element::~Element() {

	}

	void Element::draw(engine::Program& material) {
		texture.use(0);

		model = get_transform();

		material.set("model", model);

		engine::Renderer2D::draw_quad();
	}

	Button::Button(const std::function<void()>& event, engine::Texture2D& texture, glm::vec2 position, glm::vec2 size) :
		Element(texture, position, size),
		function(event), 
		handle(application->events.event_subscribe(engine::MouseClickEvent, on_click))
	{

	}

	Button::~Button() {
		application->events.event_unsubscribe(handle);
	}

	bool Button::touching(glm::ivec2 pos) {
		glm::ivec2 corner = glm::ivec2(position) + glm::ivec2(size);

		return pos.x >= position.x && pos.y >= position.y && pos.x <= corner.x && pos.y <= corner.y;
	}

	void Button::on_click(const engine::MouseClickEvent* e) {
		if (touching(e->pos)) {
			if (e->button == 0 && e->action == 1) {
				function();
			}
		}
	}
}