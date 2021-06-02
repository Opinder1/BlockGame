#include "ui.h"

namespace ui {
	Element::Element(engine::Program& material, engine::Texture2D& texture, glm::vec2 position, glm::vec2 size) :
		material(material),
		texture(texture),
		engine::Transform2D{ position },
		size(size),
		rot(0)
	{

	}

	Element::~Element() {

	}

	void Element::draw() {
		texture.use(0);

		material.set("pos", position);

		material.set("rot", rot);
		rot += 0.01;

		engine::Renderer2D::draw_quad();
	}

	Button::Button(const std::function<void()>& event, engine::Program& material, engine::Texture2D& texture, glm::vec2 position, glm::vec2 size) :
		Element(material, texture, position, size),
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