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

			for (auto&& [entity, transform, button] : registry.view<engine::Transform2D, ButtonComponent>().each()) {
				glm::vec2 bottom_left = transform.position - transform.scale / 2;
				glm::vec2 top_right = transform.position + transform.scale / 2;

				if (touches_rectangle(pos, bottom_left, top_right)) {
					button.function();
				}
			}
		}
	}
}