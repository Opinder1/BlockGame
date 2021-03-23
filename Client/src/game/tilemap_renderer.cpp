#include "tilemap_renderer.h"

namespace tilemap {
	std::vector<glm::vec3> vertexes = {
		{0, 0, 0}, {0, 0, 1}, {0, 1, 1},
		{0, 0, 0}, {0, 1, 1}, {0, 1, 0},
		{1, 1, 0}, {0, 0, 0}, {0, 1, 0},
		{1, 0, 1}, {0, 0, 0}, {1, 0, 0},
		{1, 1, 0}, {1, 0, 0}, {0, 0, 0},
		{1, 0, 1}, {0, 0, 1}, {0, 0, 0},
		{0, 1, 1}, {0, 0, 1}, {1, 0, 1},
		{1, 1, 1}, {1, 0, 0}, {1, 1, 0},
		{1, 1, 1}, {0, 1, 0}, {0, 1, 1},
		{1, 1, 1}, {1, 0, 1}, {1, 0, 0},
		{1, 1, 1}, {1, 1, 0}, {0, 1, 0},
		{1, 1, 1}, {0, 1, 1}, {1, 0, 1}
	};

	engine::ArrayBuffer* vertex_buffer;
	engine::Array* array;

	engine::Material* material;

	void init() {
		vertex_buffer = new engine::ArrayBuffer();
		array = new engine::Array();

		vertex_buffer->set_data(vertexes.size(), vertexes.data(), engine::BufferType::Static);
		array->set_attribute(0, *vertex_buffer, engine::Type::float32, 3);

		material = new engine::Material("tilemap");

		material->set("texture_data", 0);
		material->set("heightmap_data", 1);
	}

	void deinit() {
		delete array;
		delete vertex_buffer;
		delete material;
	}

	void set_camera_rot(const glm::vec3& rot) {
		material->set("camera_rot", rot);
	}

	void set_camera_pos(const glm::vec3& pos) {
		material->set<glm::vec3>("camera_pos", { pos.z, pos.y, pos.x });
	}

	void set_screen_size(const glm::uvec2& size) {
		material->set("screen_size", glm::vec2(size));
	}

	void draw(const glm::vec3& pos, const glm::vec3& size) {
		glm::mat4 transform = glm::mat4(1.0f);

		transform = glm::translate(transform, pos);
		transform = glm::scale(transform, size);

		material->use();

		material->set("transform", transform);

		material->set("cuboid_pos", glm::vec3(pos));
		material->set("cuboid_size", glm::vec3(size));

		array->draw(engine::DrawType::Default, (uint32)vertexes.size());
	}
}