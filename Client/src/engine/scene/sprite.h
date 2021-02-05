#pragma once

#include <ocode.h>

#include <GL/glew.h>
#include <GLM/glm.hpp>

#include "../renderer/array.h"
#include "../renderer/framebuffer.h"
#include "material.h"

namespace engine {
	class QuadRenderer {
	protected:
		void draw();

	public:
		static void init();
		static void deinit();

		static void set_material(Material* material);

		void set_position(const glm::vec2& position);
		void set_scale(const glm::vec2& scale);
		void set_rotation(float rotation);
	};
	
	class Sprite : public QuadRenderer {
	public:
		static Material* default_material;

	protected:
		TextureBuffer& texture;

	public:
		Sprite(TextureBuffer& texture) : texture(texture) {}

		void draw();
		void draw(const glm::vec2& position);
		void draw(const glm::vec2& position, const glm::vec2& scale, float rotation);
	};

	class MSSprite : public QuadRenderer {
	public:
		static Material* default_material;

	protected:
		MSTextureBuffer& texture;

	public:
		MSSprite(MSTextureBuffer& texture) : texture(texture) {}

		void draw();
	};
}