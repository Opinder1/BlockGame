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

	engine::ArrayBuffer vertex_buffer;
	engine::Array array;

	engine::Program program;

	void init() {
		vertex_buffer._new();
		array._new();

		vertex_buffer.set_data(vertexes.data(), vertexes.size(), engine::BufferType::Static);
		array.set_attribute(0, vertex_buffer, engine::Type::float32, 3);

		program._new();
		//material = new engine::Material("tilemap"s);

		program.set("texture_data", 0);
		program.set("heightmap_data", 1);
	}

	void deinit() {
		array._delete();
		vertex_buffer._delete();
		program._delete();
	}

	void set_camera_rot(const glm::vec3& rot) {
		program.set("camera_rot", rot);
	}

	void set_camera_pos(const glm::vec3& pos) {
		program.set<glm::vec3>("camera_pos", { pos.z, pos.y, pos.x });
	}

	void set_screen_size(const glm::uvec2& size) {
		program.set("screen_size", glm::vec2(size));
	}

	void draw(const glm::vec3& pos, const glm::vec3& size) {
		glm::mat4 transform = glm::mat4(1.0f);

		transform = glm::translate(transform, pos);
		transform = glm::scale(transform, size);

		program.use();

		program.set("transform", transform);

		program.set("cuboid_pos", glm::vec3(pos));
		program.set("cuboid_size", glm::vec3(size));

		array.draw(engine::DrawType::Triangles, (glm::uint32)vertexes.size());
	}
}