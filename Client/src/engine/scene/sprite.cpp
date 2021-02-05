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

	Material* Sprite::default_material = NULL;
	Material* MSSprite::default_material = NULL;


	void QuadRenderer::init() {
		quad_array = new Array();
		quad_vertex_array = new ArrayBuffer();

		quad_array->set_attribute(0, *quad_vertex_array, Type::uint8, 2);

		quad_vertex_array->set_data(quad_vertexes.size(), quad_vertexes.data(), BufferType::Static);

		Sprite::default_material = new Material("sprite");
		MSSprite::default_material = new Material("multisample_sprite");
	}

	void QuadRenderer::deinit() {
		delete quad_array;
		delete quad_vertex_array;

		delete Sprite::default_material;
		delete MSSprite::default_material;
	}

	void QuadRenderer::set_material(Material* material) {
		quad_material = material;
		quad_material->use();
		quad_material->set("pos", glm::vec2(0, 0));
		quad_material->set("scale", glm::vec2(1, 1));
		quad_material->set("rot", 0.0f);
	}

	void QuadRenderer::set_position(const glm::vec2& position) {
		quad_material->set("pos", position);
	}

	void QuadRenderer::set_scale(const glm::vec2& scale) {
		quad_material->set("scale", scale);
	}

	void QuadRenderer::set_rotation(float rotation) {
		quad_material->set("rot", rotation);
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
		quad_material->set("size", texture.get_size());
		quad_material->set("samples", texture.get_samples());
		QuadRenderer::draw();
	}
}