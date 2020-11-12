#pragma once

#include <ocode.h>

#include <GL/glew.h>

namespace engine {
	class Polygon {
	private:
		uint32 vao;
		uint32 vbo;

	public:
		Polygon(const Polygon&) = delete;
		Polygon();
		~Polygon();

		void draw();
	};
}