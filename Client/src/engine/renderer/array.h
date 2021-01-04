#pragma once

#include <ocode.h>

#include <GL/glew.h>
#include <GLM/glm.hpp>

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

		void draw_elements(uint32 elements);
		void draw_elements_instanced(uint32 elements, uint32 instances);
	};

	class MultiElementArray : ElementArray, public DrawCallBuffer {
	public:
		MultiElementArray() : ElementArray() {}

		void new_object();
		void delete_object(); // Will have to update whole buffer as well as draw call buffer

		void multi_draw_elements(uint32 elements);
		void multi_draw_elements_instanced(uint32 elements, uint32 instances);
	};
}