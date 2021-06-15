#include "texture.h"

namespace engine {
	_Texture::_Texture(glm::uvec2 size, TextureFormat format) : data(new glm::uint8[size.x, size.y, (glm::uint8)format]), owns_data(true), size(size), format(format) {

	}

	_Texture::_Texture(glm::uint8* data, glm::uvec2 size, TextureFormat format) : data(data), owns_data(false), size(size), format(format) {

	}

	_Texture::~_Texture() {
		if (owns_data) delete data;
	}

	glm::uint8* _Texture::get_data() const {
		return data;
	}

	glm::uvec2 _Texture::get_size() const {
		return size;
	}

	TextureFormat _Texture::get_format() const {
		return format;
	}
}