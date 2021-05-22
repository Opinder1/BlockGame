#include "../renderer/array.h"

#include "opengl.h"

namespace engine {
	GLenum drawtype_index[] = { GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_PATCHES };

	glm::uint32 current_array = 0;

	Array::Array() {
		glGenVertexArrays(1, &vertex_array_id);
	}

	Array::~Array() {
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
		glDrawArrays(drawtype_index[(glm::uint32)type], 0, vertexes);
	}

	void Array::draw_instanced(DrawType type, glm::uint32 vertexes, glm::uint32 instances) {
		use();
		glDrawArraysInstanced(drawtype_index[(glm::uint32)type], 0, vertexes, instances);
	}

	void ElementArray::draw(glm::uint32 elements) {
		Array::use();
		glDrawElements(GL_TRIANGLES, elements, gl_type(element_type), 0);
	}

	void ElementArray::draw_instanced(glm::uint32 elements, glm::uint32 instances) {
		Array::use();
		glDrawElementsInstanced(GL_TRIANGLES, elements, gl_type(element_type), 0, instances);
	}
}