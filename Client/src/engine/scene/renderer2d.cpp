#include "renderer2d.h"

namespace engine {
	std::vector<glm::u8vec2> quad_vertexes = {
		{0, 0},
		{1, 0},
		{0, 1},
		{1, 1}
	};

	struct Quad {
		Array array;
		ArrayBuffer vertex_array;
	} quad;

	int Renderer2D::camera_buffer_slot = 1;

	void Renderer2D::init() {
		quad.array._new();
		quad.vertex_array._new();

		quad.array.set_attribute(0, quad.vertex_array, Type::uint8, 2);

		quad.vertex_array.create(quad_vertexes.size(), quad_vertexes.data(), BufferType::Static);
	}

	void Renderer2D::shutdown() {
		quad.array._delete();
		quad.vertex_array._delete();
	}

	void Renderer2D::draw_quad() {
		// TODO could be replaced with drawing a varied size point.
		quad.array.draw(DrawType::Strips, 4);
	}
}