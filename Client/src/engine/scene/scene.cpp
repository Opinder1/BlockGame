#include "scene.h"

namespace engine {
	Scene2D::Scene2D(glm::vec2 size) : size(size) {
		frame._new();
		texture._new();
		texture.set_empty(size);
		frame.set_attachment(texture, 0);
	}

	Scene2D::~Scene2D() {
		frame._delete();
		texture._delete();
	}

	void Scene2D::use() {
		frame.clear();
	}

	void Scene2D::set_size(const glm::vec2& new_size) {
		size = new_size;
		texture.set_empty(new_size);
	}

	glm::vec2 Scene2D::get_size() {
		return size;
	}

	Texture2D Scene2D::get_texture() {
		return texture;
	}
}