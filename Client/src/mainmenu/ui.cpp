#include "ui.h"

namespace ui {
	Element::Element(engine::Material* material, engine::TextureBuffer* texture, glm::vec2 position) :
		material(material),
		texture(texture),
		engine::Transform2D(position)
	{

	}

	Element::~Element() {

	}

	void Element::draw() {
		texture->use(0);

		material->set("pos", position);
		material->set("texture_size", texture->get_size());

		engine::QuadRenderer::draw();
	}

	Button::Button(const std::function<void()>& event, engine::Material* material, engine::TextureBuffer* texture, glm::vec2 position) :
		Element(material, texture, position),
		function(event), 
		handle(application->events.event_subscribe(engine::MouseClickEvent, on_click))
	{

	}

	Button::~Button() {
		application->events.event_unsubscribe(handle);
	}

	bool Button::touching(glm::ivec2 pos) {
		glm::ivec2 corner = glm::ivec2(position) + glm::ivec2(texture->get_size());

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