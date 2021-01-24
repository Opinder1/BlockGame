#pragma once

#include <ocode.h>

#include <string>
#include <rapidjson/document.h>

#include <GLM/glm.hpp>

namespace engine {
	struct Pixel {
		uint8 r, g, b, a;
	};

	//template<class PixelType = Pixel>
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