#pragma once

#include <ocode.h>

#include <string>
#include <rapidjson/document.h>

#include "gl.h"

namespace engine {
	struct RGBA { // GL_RGBA
		glm::uint8 r, g, b, a;
	};

	struct R { // GL_RED
		glm::uint8 r;
	};

	struct Pixel : public RGBA {};

	//template<class Pixel = RGBA>
	class Texture {
	private:
		Pixel* data;

		glm::uvec2 size;

	protected:
		void _set_at(glm::uvec2 pos, Pixel pixel);
		Pixel& _get_at(glm::uvec2 pos) const;

	public:
		Texture(const Texture&) = delete;
		Texture(glm::uvec2 size);
		Texture(const std::string& name);
		~Texture();

		glm::uvec2 get_size() const;

		void set_at(glm::uvec2 pos, Pixel pixel);
		Pixel get_at(glm::uvec2 pos) const;

		Pixel* get_data() const;

		Pixel& operator[](glm::uvec2 pos);
	};
}