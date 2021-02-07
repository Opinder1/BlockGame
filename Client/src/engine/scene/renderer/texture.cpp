#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace engine {
	Texture::Texture(glm::uvec2 size) : size(size) {
		data = new Pixel[size.x, size.y];
	}

	Texture::Texture(const std::string& name) : size(0, 0), data(NULL) {
		std::string file_name = std::string(PROJECT_DIR) + "resources\\textures\\" + name;

		if (!ocode::file_exists(file_name)) {
			printf("File %s does not exist\n", file_name.c_str());
			return;
		}

		int32 n;
		data = (Pixel*)stbi_load(file_name.c_str(), (int*)&size.x, (int*)&size.y, &n, 4);

		if (n != 4) {
			throw "Could not load image";
		}
	}

	Texture::~Texture() {
		delete data;
	}

	void Texture::_set_at(glm::uvec2 pos, Pixel pixel) {
		data[pos.x + pos.y * size.x] = pixel;
	}

	Pixel& Texture::_get_at(glm::uvec2 pos) const {
		return data[pos.x + pos.y * size.x];
	}

	Pixel* Texture::get_data() const {
		return data;
	}

	glm::uvec2 Texture::get_size() const {
		return size;
	}

	void Texture::set_at(glm::uvec2 pos, Pixel pixel) {
		if (pos.x < 0) pos.x = 0;
		if (pos.y < 0) pos.y = 0;
		if (pos.x > size.x) pos.x = size.x;
		if (pos.y > size.y) pos.y = size.y;

		_set_at(pos, pixel);
	}

	Pixel Texture::get_at(glm::uvec2 pos) const {
		if (pos.x < 0) pos.x = 0;
		if (pos.y < 0) pos.y = 0;
		if (pos.x > size.x) pos.x = size.x;
		if (pos.y > size.y) pos.y = size.y;

		return _get_at(pos);
	}

	Pixel& Texture::operator[](glm::uvec2 pos) {
		if (pos.x < 0) pos.x = 0;
		if (pos.y < 0) pos.y = 0;
		if (pos.x > size.x) pos.x = size.x;
		if (pos.y > size.y) pos.y = size.y;

		return _get_at(pos);
	}
}