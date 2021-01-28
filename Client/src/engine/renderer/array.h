#pragma once

#include <ocode.h>

#include "buffer.h"

namespace engine {
	class Array {
	private:
		uint32 vertex_array_id;

	protected:
		void use();

	public:
		Array(const Array&) = delete;
		Array();
		~Array();

		void set_attribute(uint32 pos, ArrayBuffer& buffer, Type type, uint32 width = 1, uint32 height = 1, uint32 divisor = 0);

		void draw(uint32 type, uint32 vertexes);
		void draw_instanced(uint32 type, uint32 vertexes, uint32 instances);
	};

	class ElementArray : public Array, public ElementBuffer {
	private:
		Type element_type;

	public:
		ElementArray(Type type) : Array(), ElementBuffer(), element_type(type) {}

		void draw(uint32 elements);
		void draw_instanced(uint32 elements, uint32 instances);
	};
}