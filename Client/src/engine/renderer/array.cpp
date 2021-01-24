#include "array.h"

namespace engine {
	Array::Array() {
		glGenVertexArrays(1, &vertex_array_id);
		bind();
	}

	Array::~Array() {
		glDeleteVertexArrays(1, &vertex_array_id);
	}

	void Array::bind() {
		glBindVertexArray(vertex_array_id);
	}

	void Array::draw(uint32 type, uint32 vertexes) {
		bind();
		glDrawArrays(type, 0, vertexes);
	}

	void Array::draw_instanced(uint32 type, uint32 vertexes, uint32 instances) {
		bind();
		glDrawArraysInstanced(type, 0, vertexes, instances);
	}

	void ElementArray::draw(uint32 elements) {
		Array::bind();
		glDrawElements(GL_TRIANGLES, elements, element_type, 0);
	}

	void ElementArray::draw_instanced(uint32 elements, uint32 instances) {
		Array::bind();
		glDrawElementsInstanced(GL_TRIANGLES, elements, element_type, 0, instances);
	}
}