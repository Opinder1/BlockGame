#include "array.h"

#include "opengl.h"

namespace engine {
	GLenum drawtype_index[] = { GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_PATCHES };

	uint32 current_array = 0;

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

	void Array::set_attribute(uint32 pos, ArrayBuffer& buffer, Type type, uint32 width, uint32 height, uint32 divisor) {
		use();
		buffer.use();

		for (uint32 i = 0; i < height; i++) {
			glEnableVertexAttribArray(pos + i);
			glVertexAttribPointer(pos + i, width, gl_type(type), GL_FALSE, width * height * type_size(type), (void*)uint64(i * height * type_size(type)));

			if (divisor) {
				glVertexAttribDivisor(pos + i, divisor);
			}
		}
	}

	void Array::draw(DrawType type, uint32 vertexes) {
		use();
		glDrawArrays(drawtype_index[(uint32)type], 0, vertexes);
	}

	void Array::draw_instanced(DrawType type, uint32 vertexes, uint32 instances) {
		use();
		glDrawArraysInstanced(drawtype_index[(uint32)type], 0, vertexes, instances);
	}

	void ElementArray::draw(uint32 elements) {
		Array::use();
		glDrawElements(GL_TRIANGLES, elements, gl_type(element_type), 0);
	}

	void ElementArray::draw_instanced(uint32 elements, uint32 instances) {
		Array::use();
		glDrawElementsInstanced(GL_TRIANGLES, elements, gl_type(element_type), 0, instances);
	}
}