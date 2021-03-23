#include "ui.h"

namespace ui {
	Element::Element(engine::Material& material, engine::TextureBuffer& texture, glm::vec2 position) : material(material), texture(texture), engine::Transform2D(position) {

	}

	Element::~Element() {

	}

	void Element::draw() {
		texture.use(0);

		material.set("pos", position);
		material.set("texture_size", texture.get_size());

		engine::QuadRenderer::draw();
	}
}