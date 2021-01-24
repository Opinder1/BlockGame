#pragma once

#include <ocode.h>

#include "opengl.h"

#include "buffer.h"

namespace engine {
	class Array {
	private:
		uint32 vertex_array_id;

	protected:
		void bind();

	public:
		Array(const Array&) = delete;
		Array();
		~Array();

		void draw(uint32 type, uint32 vertexes);
		void draw_instanced(uint32 type, uint32 vertexes, uint32 instances);
	};

	class ElementArray : public Array, public ElementBuffer {
	public:
		ElementArray() : Array() {}

		void draw(uint32 elements);
		void draw_instanced(uint32 elements, uint32 instances);
	};
}