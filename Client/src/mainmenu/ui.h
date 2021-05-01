#pragma once

#include "../engine/engine.h"

namespace ui {
	class Element : public engine::Transform2D {
	protected:
		engine::Material& material;
		engine::TextureBuffer& texture;

	public:
		Element(engine::Material& material, engine::TextureBuffer& texture, glm::vec2 position = { 0, 0 });
		~Element();

		void draw();
	};

	typedef std::vector<std::unique_ptr<ui::Element>> Frame;

	class Button : public Element {
	private:
		bool touching(glm::ivec2 pos);

	protected:
		std::function<void()> function;

		ocode::ObserverHandle handle;

	public:
		Button(const std::function<void()>& event, engine::Material& material, engine::TextureBuffer& texture, glm::vec2 position);
		~Button();

	protected:
		void on_click(const engine::MouseClickEvent* e);
	};
}

