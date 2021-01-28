#include "sprite.h"

namespace engine {
	std::vector<glm::u8vec2> square_vertexes = {
		{0, 0},
		{1, 0},
		{0, 1},
		{1, 1}
	};

	Array* array;
	ArrayBuffer* vertex_array;
	Material* sprite_material;

	Material* default_sprite_material;

	void Sprite::init() {
		array = new Array();
		vertex_array = new ArrayBuffer();

		array->set_attribute(0, *vertex_array, Type::uint8, 2);

		vertex_array->data(square_vertexes.size(), square_vertexes.data(), BufferType::Static);

		default_sprite_material = new Material("sprite");
	}

	void Sprite::deinit() {
		delete array;
		delete vertex_array;
		delete default_sprite_material;
	}

	void Sprite::set_material(Material* material) {
		sprite_material = material;
		sprite_material->use();
		sprite_material->set_vec2("pos", { 0, 0 });
		sprite_material->set_vec2("scale", { 1, 1 });
		sprite_material->set_float("rot", 0);
	}

	Sprite::Sprite(TextureBuffer& texture) : texture(texture) {

	}

	Sprite::~Sprite() {

	}

	void Sprite::set_position(const glm::vec2& position) {
		sprite_material->set_vec2("pos", position);
	}

	void Sprite::set_scale(const glm::vec2& scale) {
		sprite_material->set_vec2("scale", scale);
	}

	void Sprite::set_rotation(float rotation) {
		sprite_material->set_float("rot", rotation);
	}

	void Sprite::draw() {
		texture.activate_slot(0);
		array->draw(GL_TRIANGLE_STRIP, 4);
	}

	void Sprite::draw(const glm::vec2& position, const glm::vec2& scale, float rotation) {
		set_position(position);
		set_scale(scale);
		set_rotation(rotation);

		draw();
	}

	void Sprite::draw_multiple(uint32 count) {
		array->draw(GL_TRIANGLE_STRIP, 4);
	}
}