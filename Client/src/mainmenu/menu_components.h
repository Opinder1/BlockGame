 #pragma once

#include "menu.h"

namespace ui {
	struct HiddenComponent {

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

	template <class Type>
	class Sprite {
	protected:
		inline static engine::Program shader;

		inline static engine::Texture2D texture;

		inline static glm::uvec2 size;

	public:
		static void init(engine::Program& shader, const engine::Texture& texture_data) {
			Sprite::shader = shader;
			size = texture_data.get_size();
			texture._new();
			texture.set_filter(engine::TextureFilter::Linear, engine::TextureFilter::Linear);
			texture.set_data(texture_data);
		}

		static void shutdown() {
			texture._delete();
		}

		static entt::entity create(entt::registry& registry, const glm::vec2& pos, float rotation) {
			auto entity = registry.create();

			registry.emplace<engine::Transform2D>(entity, pos, rotation, size);
			registry.emplace<Type>(entity);

			return entity;
		}

		static void update(entt::registry& registry) {
			auto view = registry.view<engine::Transform2D, Type>(entt::exclude<HiddenComponent>);

			Type::shader.use();

			Type::texture.use(0);

			for (auto&& [entity, transform] : view.each()) {
				Type::shader.set("model", transform.get_transform());

				engine::Renderer2D::draw_quad();
			}
		}
	};

	class Background : public ui::Sprite<Background> {

	};

	class BasicButton : public ui::Sprite<BasicButton> {
	private:
		inline static engine::Font text_font;

	public:
		static void init(engine::Program& shader, const engine::Texture& texture_data, const engine::Font& font) {
			ui::Sprite<BasicButton>::init(shader, texture_data);

			text_font = font;
		}

		static entt::entity create(entt::registry& registry, const std::string& text, const glm::vec2& pos, float rotation, const std::function<void()>& function) {
			auto button = ui::Sprite<BasicButton>::create(registry, pos, rotation);

			registry.emplace<TextComponent>(button, text);
			registry.emplace<ButtonComponent>(button, function);

			return button;
		}

		static void update(entt::registry& registry) {
			ui::Sprite<BasicButton>::update(registry);

			// TODO Should be looping BasicButton not TextComponent
			auto view = registry.view<engine::Transform2D, TextComponent>(entt::exclude<HiddenComponent>);

			for (auto&& [entity, transform, text] : view.each()) {
				text_font->get_shader().set("model", glm::rotate(glm::translate(glm::vec3(transform.position, 0)), transform.rotation, glm::vec3(0, 0, 1)));

				text_font->render(text.text, text.pos, text.scale, text.color);
			}
		}
	};
}

