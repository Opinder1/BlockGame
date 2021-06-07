#include "../gl/array.h"

#include "opengl.h"

namespace engine {
	glm::uint32 current_array = 0;

	void Array::_new() {
		glGenVertexArrays(1, &vertex_array_id);
	}

	void Array::_delete() {
		glDeleteVertexArrays(1, &vertex_array_id);
	}

	void Array::use() {
		if (current_array != vertex_array_id) {
			glBindVertexArray(vertex_array_id);
			current_array = vertex_array_id;
		}
	}

	void Array::set_attribute(glm::uint32 pos, ArrayBuffer& buffer, Type type, glm::uint32 width, glm::uint32 height, glm::uint32 divisor) {
		use();
		buffer.use();

		for (glm::uint32 i = 0; i < height; i++) {
			glEnableVertexAttribArray(pos + i);
			glVertexAttribPointer(pos + i, width, gl_type(type), GL_FALSE, width * height * type_size(type), NULL);

			if (divisor) {
				glVertexAttribDivisor(pos + i, divisor);
			}
		}
	}

	void Array::draw(DrawType type, glm::uint32 vertexes) {
		use();
		GLEW_GET_FUN(glDrawArrays)(draw_type(type), 0, vertexes);
	}

	void Array::draw_instanced(DrawType type, glm::uint32 vertexes, glm::uint32 instances) {
		use();
		glDrawArraysInstanced(draw_type(type), 0, vertexes, instances);
	}

	void ElementArray::_new(Type type) {
		element_type = type;
		Array::_new();
		ElementBuffer::_new();
		ElementBuffer::use();
	}

	void ElementArray::_delete() {
		Array::_delete();
		ElementBuffer::_delete();
	}

	void ElementArray::draw(DrawType type, glm::uint32 elements) {
		Array::use();
		GLEW_GET_FUN(glDrawElements)(draw_type(type), elements, gl_type(element_type), 0);
	}

	void ElementArray::draw_instanced(DrawType type, glm::uint32 elements, glm::uint32 instances) {
		Array::use();
		glDrawElementsInstanced(draw_type(type), elements, gl_type(element_type), 0, instances);
	}
}