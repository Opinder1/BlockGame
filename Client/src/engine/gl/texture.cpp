#include "texture.h"

namespace engine {
	Texture::Texture(glm::uvec2 size, TextureFormat format) : data(new glm::uint8[size.x, size.y, (glm::uint8)format]), owns_data(true), size(size), format(format) {

	}

	Texture::Texture(glm::uint8* data, glm::uvec2 size, TextureFormat format) : data(data), owns_data(false), size(size), format(format) {

	}

	Texture::~Texture() {
		if (owns_data) delete data;
	}

	glm::uint8* Texture::get_data() const {
		return data;
	}

	glm::uvec2 Texture::get_size() const {
		return size;
	}

	TextureFormat Texture::get_format() const {
		return format;
	}
}