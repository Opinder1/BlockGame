#pragma once

#include "../engine/engine.h"

namespace ui {
	class Element : public engine::Transform2D {
	private:
		engine::Material& material;
		engine::TextureBuffer& texture;

	public:
		Element(engine::Material& material, engine::TextureBuffer& texture, glm::vec2 position = { 0, 0 });
		~Element();

		void draw();
	};

	class Button : public Element {
		std::function<void()> event;

		Button();
		~Button();
	};
}

