#pragma once

#include <ocode.h>

#include <GL/glew.h>

namespace engine {
	class Polygon {
	private:
		uint32 vertex_array_id;
		uint32 vertex_buffer_id;

	public:
		Polygon(const Polygon&) = delete;
		Polygon();
		Polygon(float* data);
		~Polygon();

		void draw();

		static void unbind();
	};

	class Mesh {
		Polygon* polygons;
	};
}