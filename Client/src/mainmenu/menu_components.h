 #pragma once

#include "menu.h"

namespace ui {
	struct HiddenComponent {

	};

	struct TransformComponent : public engine::Transform2D {

	};

	struct ButtonComponent {
		std::function<void()> function;

		static void update(entt::registry& registry, const engine::MouseClickEvent* e, const glm::mat4& camera);
	};

	struct TextComponent {
		std::string text;

		// TODO remove pos and scale as they make no sense. Color could be dependent on shader so idk yet.
		glm::vec2 pos;
		glm::float32 scale;
		glm::vec3 color;

		TextComponent(const std::string& text, const glm::vec2& pos = { -110, -10 }, glm::float32 scale = 1, glm::vec3 color = { 1, 1, 1 }) : text(text), pos(pos), scale(scale), color(color) {}
	};

	class Sprite : public EntityType {
	private:
		engine::Program shader;
		engine::Texture2D texture;
		glm::uvec2 size;

	public:
		Sprite(engine::Program shader, engine::Texture texture_data);

		~Sprite();

		void create(entt::registry& registry, entt::entity entity, const glm::vec2& pos, float rotation);

		void update(entt::registry& registry, std::vector<entt::entity>& entities) override;
	};

	class BasicButton : public Sprite {
	private:
		engine::Font text_font;

	public:
		BasicButton(engine::Program shader, engine::Texture texture_data, engine::Font font) : Sprite(shader, texture_data), text_font(font) {}

		void create(entt::registry& registry, entt::entity entity, const std::string& text, const glm::vec2& pos, float rotation, const std::function<void()>& function);

		void update(entt::registry& registry, std::vector<entt::entity>& entities) override;
	};
}

