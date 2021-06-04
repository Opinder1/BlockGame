 #pragma once

#include "../application.h"

namespace ui {
	class Element : public engine::Transform2D {
	protected:
		engine::Texture2D& texture;

		glm::uvec2 size;

		glm::mat4 model;

	public:
		Element(engine::Texture2D& texture, glm::vec2 position, glm::vec2 size);
		~Element();

		void draw(engine::Program& material);
	};

	class ElementInstance {
	protected:
		glm::uvec2 size;

		glm::mat4 model;
	};

	class ElementInstanced {
	protected:
		engine::Program& material;
		engine::Texture2D& texture;

		std::vector<Element*> instances;

	public:
		void submit(Element* new_element);
		
		void draw();
	};

	class Button : public Element {

	protected:
		std::function<void()> function;

		ocode::ObserverHandle handle;

	public:
		Button(const std::function<void()>& event, engine::Texture2D& texture, glm::vec2 position, glm::vec2 size);
		~Button();

	private:
		bool touching(glm::ivec2 pos);

		void on_click(const engine::MouseClickEvent* e);
	};
}

