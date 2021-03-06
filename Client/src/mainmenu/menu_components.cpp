#include "menu_components.h"

namespace ui {
	float tri_area(glm::vec2& A, glm::vec2& B, glm::vec2& C) {
		return abs((B.x * A.y - A.x * B.y) + (C.x * B.y - B.x * C.y) + (A.x * C.y - C.x * A.y)) / 2.0f;
	}

	bool touches_rectangle_rotated(glm::vec2& point, glm::vec2& A, glm::vec2& B, glm::vec2& C, glm::vec2& D) {
		auto rectangle_area = glm::length(B - A) * glm::length(D - A);

		auto parts_area = tri_area(A, B, point) + tri_area(B, C, point) + tri_area(C, D, point) + tri_area(D, A, point);

		return parts_area <= rectangle_area;
	}

	bool touches_rectangle(glm::vec2& point, glm::vec2& A, glm::vec2& B) {
		return point.x >= A.x && point.y >= A.y && point.x <= B.x && point.y <= B.y;
	}

	void ButtonComponent::update(entt::registry& registry, const engine::MouseClickEvent* e, const glm::mat4& camera) {
		if (e->button == 0 && e->action == 1) {
			glm::vec2 pos = e->pos - glm::ivec2(application->window.get_size() / 2);

			pos = glm::inverse(camera) * glm::vec4(pos, 0, 0);

			for (auto&& [entity, transform, button] : registry.view<TransformComponent, ButtonComponent>().each()) {
				glm::vec2 bottom_left = transform.position - transform.scale / 2;
				glm::vec2 top_right = transform.position + transform.scale / 2;

				if (touches_rectangle(pos, bottom_left, top_right)) {
					button.function();
				}
			}
		}
	}

	Sprite::Sprite(engine::Program shader, engine::Texture texture_data) : shader(shader), size(texture_data->get_size()) {
		texture._new();
		texture.set_filter(engine::TextureFilter::Linear, engine::TextureFilter::Linear);
		texture.set_wrap(engine::TextureWrap::Repeat, engine::TextureWrap::Repeat);
		texture.set_data(texture_data);
	}

	Sprite::~Sprite() {
		texture._delete();
	}

	void Sprite::create(entt::registry& registry, entt::entity entity, const glm::vec2& pos, float rotation) {
		registry.emplace<TransformComponent>(entity, pos, rotation, size);
	}

	void Sprite::update(entt::registry& registry, std::vector<entt::entity>& entities) {
		auto view = registry.view<TransformComponent>(entt::exclude<HiddenComponent>);

		shader.use();

		texture.use(0);

		for (auto& entity : entities) {
			auto [transform] = view.get(entity);

			shader.set("model", transform.get_transform());

			engine::Renderer2D::draw_quad();
		}
	}

	void BasicButton::create(entt::registry& registry, entt::entity entity, const std::string& text, const glm::vec2& pos, float rotation, const std::function<void()>& function) {
		Sprite::create(registry, entity, pos, rotation);

		registry.emplace<ButtonComponent>(entity, function);
		registry.emplace<TextComponent>(entity, text);
	}

	void BasicButton::update(entt::registry& registry, std::vector<entt::entity>& entities) {
		Sprite::update(registry, entities);

		auto view = registry.view<TransformComponent, TextComponent>(entt::exclude<HiddenComponent>);

		for (auto& entity : entities) {
			auto [transform, text] = view.get(entity);

			text_font->get_shader().set("model", glm::rotate(glm::translate(glm::vec3(transform.position, 0)), transform.rotation, glm::vec3(0, 0, 1)));

			text_font->render(text.text, text.pos, text.scale, text.color);
		}
	}
}