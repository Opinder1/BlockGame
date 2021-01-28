#pragma once

#include <ocode.h>

#include <GL/glew.h>
#include <GLM/glm.hpp>

#include "../renderer/array.h"
#include "../renderer/framebuffer.h"
#include "material.h"

namespace engine {
	extern Material* default_sprite_material;
	
	class Sprite {
	protected:
		TextureBuffer& texture;

	public:
		static void init();
		static void deinit();
		static void set_material(Material* material);

		Sprite(TextureBuffer& texture);
		~Sprite();

		void set_position(const glm::vec2& position);
		void set_scale(const glm::vec2& scale);
		void set_rotation(float rotation);

		void draw();
		void draw(const glm::vec2& position, const glm::vec2& scale, float rotation);
		void draw_multiple(uint32 count);
	};
}