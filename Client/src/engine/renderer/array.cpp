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

	void Array::draw(GLenum type, size_t vertexes) {
		bind();
		glDrawArrays(type, 0, (uint32)vertexes);
	}

	void Array::draw_elements(GLenum type, size_t elements) {
		bind();
		glDrawElements(type, (uint32)elements, GL_UNSIGNED_INT, 0);
	}

	void Array::draw_instanced(GLenum type, size_t vertexes, size_t instances) {
		bind();
		glDrawArraysInstanced(type, 0, (uint32)vertexes, (uint32)instances);
	}

	void Array::draw_elements_instanced(GLenum type, size_t elements, size_t instances) {
		bind();
		glDrawElementsInstanced(type, (uint32)elements, GL_UNSIGNED_INT, 0, (uint32)instances);
	}
}