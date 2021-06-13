#pragma once

#include <ocode.h>

#include <string>
#include <rapidjson/document.h>

#include "gl.h"

namespace engine {
	class Texture {
	private:
		glm::uint8* data;
		bool owns_data;

		glm::uvec2 size;
		TextureFormat format;

	protected:
		void clamp_pos(glm::uvec2& pos);

	public:
		Texture(const Texture&) = delete;
		Texture(glm::uvec2 size, TextureFormat format);
		Texture(glm::uint8* data, glm::uvec2 size, TextureFormat format);

		~Texture();

		glm::uint8* get_data() const;

		glm::uvec2 get_size() const;

		TextureFormat get_format() const;
	};
}