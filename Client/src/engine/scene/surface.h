#pragma once

#include <ocode.h>

#include <GLM/glm.hpp>

#include "../renderer/array.h"
#include "../renderer/framebuffer.h"
#include "material.h"

namespace engine {
	class QuadRenderer {
	public:
		static void init();
		static void deinit();

		static void draw();
	};

	class SurfaceBase : public QuadRenderer {
	private:
		glm::uvec2 size;
		
	protected:
		FrameBuffer frame;

		SurfaceBase(const glm::uvec2& size) : size(size), frame(true) {}
		SurfaceBase() : size(0), frame() {}

	public:
		void resize(const glm::uvec2& size);

		void clear();
		void use();

		const glm::uvec2 get_size();

		void draw(TextureBuffer& texture, const glm::vec2& position = { 0, 0 }, const glm::vec2& scale = { 1, 1 }, float rotation = 0);
		void draw(MSTextureBuffer& texture, const glm::vec2& position = { 0, 0 }, const glm::vec2& scale = { 1, 1 }, float rotation = 0);
	};

	class Surface : public SurfaceBase {
	public:
		TextureBuffer texture;

		Surface(const glm::uvec2& size);

		void resize(const glm::uvec2& size);
	};

	class Surface3D : public SurfaceBase {
	private:
		DepthBuffer depth;

	public:
		MSTextureBuffer texture;

		Surface3D(const glm::uvec2& size, uint32 samples);

		void resize(const glm::uvec2& size, uint32 samples);
	};

	class WindowSurface : public SurfaceBase {
	public:
		WindowSurface(const glm::uvec2 size) : SurfaceBase(size) {}
	};
}