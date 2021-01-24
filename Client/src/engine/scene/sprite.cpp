#include "sprite.h"

namespace engine {
	std::vector<glm::u8vec2> square_vertexes = {
		{0, 0},
		{1, 0},
		{0, 1},
		{1, 1}
	};

	static Array* array;
	static ArrayBuffer* vertex_array;
	static Material* material;

	void Sprite::init() {
		array = new Array();
		vertex_array = new ArrayBuffer();
		material = new Material("sprite");

		vertex_array->format<uint8, 2>(0);

		vertex_array->data((uint32)square_vertexes.size(), square_vertexes.data(), BufferType::STATIC);
	}

	void Sprite::deinit() {
		delete array;
		delete vertex_array;
		delete material;
	}

	void Sprite::start_draw() {
		material->use();
		material->set_vec2("pos", { 0, 0 });
		material->set_vec2("scale", { 1, 1 });
		material->set_float("rot", 0);
	}

	Sprite::Sprite(const std::string& file_name) {
		texture.data(Texture(file_name));
	}

	Sprite::~Sprite() {

	}

	void Sprite::set_position(const glm::vec2& position) {
		material->set_vec2("pos", position);
	}

	void Sprite::set_scale(const glm::vec2& scale) {
		material->set_vec2("scale", scale);
	}

	void Sprite::set_rotation(float rotation) {
		material->set_float("rot", rotation);
	}

	void Sprite::draw() {
		texture.use(0);
		array->draw(GL_TRIANGLE_STRIP, 6);
	}

	void Sprite::draw(const glm::vec2& position, const glm::vec2& scale, float rotation) {
		set_position(position);
		set_scale(scale);
		set_rotation(rotation);

		draw();
	}

	void Sprite::draw_multiple(uint32 count) {
		array->draw(GL_TRIANGLE_STRIP, 6);
	}
}