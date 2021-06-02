 #pragma once

#include "../application.h"

namespace ui {
	class Element : public engine::Transform2D {
	protected:
		engine::Program& material;
		engine::Texture2D& texture;

		glm::uvec2 size;

		glm::float32 rot;

	public:
		Element(engine::Program& material, engine::Texture2D& texture, glm::vec2 position = { 0, 0 }, glm::vec2 size = { 0, 0 });
		~Element();

		void draw();
	};

	typedef std::vector<std::unique_ptr<ui::Element>> Frame;

	class Button : public Element {

	protected:
		std::function<void()> function;

		ocode::ObserverHandle handle;

	public:
		Button(const std::function<void()>& event, engine::Program& material, engine::Texture2D& texture, glm::vec2 position, glm::vec2 size);
		~Button();

	private:
		bool touching(glm::ivec2 pos);

		void on_click(const engine::MouseClickEvent* e);
	};
}

