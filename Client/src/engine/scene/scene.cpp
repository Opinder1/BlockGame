#include "scene.h"

namespace engine {
	glm::mat4 Transform2D::get_transform() const {
		glm::mat4 transform(1);
		
		transform = glm::translate(transform, glm::vec3(position, 0));
		transform = glm::rotate(transform, rotation, glm::vec3(0, 0, 1));
		transform = glm::scale(transform, glm::vec3(scale, 1));

		return transform;
	}

	Scene2D::Scene2D(glm::uvec2 size) : size(size) {
		frame._new();
		texture._new();
		texture.set_filter(TextureFilter::Linear, TextureFilter::Linear);
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

	void Scene2D::set_size(const glm::uvec2& new_size) {
		size = new_size;
		texture.set_empty(new_size);
	}

	glm::uvec2 Scene2D::get_size() {
		return size;
	}

	Texture2D Scene2D::get_texture() {
		return texture;
	}
}