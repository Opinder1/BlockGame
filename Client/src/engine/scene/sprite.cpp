#include "sprite.h"

namespace engine {
	std::vector<glm::u8vec2> quad_vertexes = {
		{0, 0},
		{1, 0},
		{0, 1},
		{1, 1}
	};

	Array* quad_array;
	ArrayBuffer* quad_vertex_array;
	Material* quad_material;

	Material* default_sprite_material;
	Material* default_mssprite_material;

	void QuadRenderer::init() {
		quad_array = new Array();
		quad_vertex_array = new ArrayBuffer();

		quad_array->set_attribute(0, *quad_vertex_array, Type::uint8, 2);

		quad_vertex_array->set_data(quad_vertexes.size(), quad_vertexes.data(), BufferType::Static);

		default_sprite_material = new Material("sprite");
		default_mssprite_material = new Material("multisample_sprite");
	}

	void QuadRenderer::deinit() {
		delete quad_array;
		delete quad_vertex_array;

		delete default_sprite_material;
		delete default_mssprite_material;
	}

	void QuadRenderer::set_material(Material* material) {
		quad_material = material;
		quad_material->use();
		quad_material->set_vec2("pos", { 0, 0 });
		quad_material->set_vec2("scale", { 1, 1 });
		quad_material->set_float("rot", 0);
	}

	void QuadRenderer::set_position(const glm::vec2& position) {
		quad_material->set_vec2("pos", position);
	}

	void QuadRenderer::set_scale(const glm::vec2& scale) {
		quad_material->set_vec2("scale", scale);
	}

	void QuadRenderer::set_rotation(float rotation) {
		quad_material->set_float("rot", rotation);
	}

	void QuadRenderer::draw() {
		quad_array->draw(DrawType::Strip, 4);
	}

	void Sprite::draw() {
		texture.activate_slot(0);
		QuadRenderer::draw();
	}

	void Sprite::draw(const glm::vec2& position) {
		set_position(position);
		draw();
	}

	void Sprite::draw(const glm::vec2& position, const glm::vec2& scale, float rotation) {
		set_position(position);
		set_scale(scale);
		set_rotation(rotation);
		draw();
	}

	void MSSprite::draw() {
		texture.activate_slot(0);
		quad_material->set_vec2("size", texture.get_size());
		quad_material->set_int32("samples", texture.get_samples());
		QuadRenderer::draw();
	}
}