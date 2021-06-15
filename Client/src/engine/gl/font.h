#pragma once

#include "array.h"
#include "shader.h"
#include "frame_buffer.h"

namespace engine {
	struct Character {
		Texture2D texture;
		glm::ivec2 size;      // size of glyph
		glm::ivec2 bearing;   // offset from baseline to left/top of glyph
		int advance;
	};

	class _Font {
	private:
		// TODO Use quadrenderer instead because it does same thing
		Array array;
		ArrayBuffer buffer;

        Program shader;

		std::vector<Character> characters;

	public:
		_Font(std::vector<Character>& characters);
		~_Font();

		// TODO Maybe?
		void set_shader(Program shader);

		Program get_shader();

		void render(const std::string& text, glm::vec2 pos, float scale, const glm::vec3& color);
	};

	using Font = _Font*;

	class Fontt {
	private:
		_Font* font;

	public:
		void _new(std::vector<Character>& characters);
		void _delete();

		void render(const std::string& text);
	};
}