#pragma once

#include <ocode.h>

#include <GL/glew.h>
#include <GLM/glm.hpp>

#include "../renderer/array.h"
#include "material.h"

namespace engine {
	class Sprite {
	protected:
		TextureBuffer texture;

	public:
		static void init();
		static void deinit();
		static void start_draw();

		Sprite(const std::string& file_name);
		~Sprite();

		void set_position(const glm::vec2& position);
		void set_scale(const glm::vec2& scale);
		void set_rotation(float rotation);

		void draw();
		void draw(const glm::vec2& position, const glm::vec2& scale, float rotation);
		void draw_multiple(uint32 count);
	};
}