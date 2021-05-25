#include "../renderer/buffer.h"

#include "opengl.h"

namespace engine {
	constexpr GLenum buffer_type(BufferType type) {
		const GLenum buffer_types[] = { GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW };
		return buffer_types[(glm::uint32)type];
	}

	glm::uint32 current_arraybuffer = 0;
	glm::uint32 current_elementbuffer = 0;
	glm::uint32 current_globalbuffer = 0;

	void BufferBase::_new() {
		glGenBuffers(1, &buffer_id);
	}

	void BufferBase::_delete() {
		glDeleteBuffers(1, &buffer_id);
	}

	void ArrayBuffer::use() {
		if (current_arraybuffer != buffer_id) {
			glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
			current_arraybuffer = buffer_id;
		}
	}

	void ArrayBuffer::new_data(glm::uint64 size, const void* data, BufferType usage) {
		use();
		glBufferData(GL_ARRAY_BUFFER, size, data, buffer_type(usage));
	}

	void ArrayBuffer::sub_data(glm::uint64 pos, glm::uint64 size, const void* data) {
		use();
		glBufferSubData(GL_ARRAY_BUFFER, pos, size, data);
	}

	void ElementBuffer::use() {
		if (current_elementbuffer != buffer_id) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
			current_elementbuffer = buffer_id;
		}
	}

	void ElementBuffer::new_data(glm::uint64 size, const void* data, BufferType usage) {
		use();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, buffer_type(usage));
	}

	void ElementBuffer::sub_data(glm::uint64 pos, glm::uint64 size, const void* data) {
		use();
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, pos, size, data);
	}

	void GlobalBuffer::use() {
		if (current_globalbuffer != buffer_id) {
			glBindBuffer(GL_UNIFORM_BUFFER, buffer_id);
			current_globalbuffer = buffer_id;
		}
	}

	void GlobalBuffer::new_data(glm::uint64 size, const void* data, BufferType usage) {
		use();
		glBufferData(GL_UNIFORM_BUFFER, size, data, buffer_type(usage));
	}

	void GlobalBuffer::sub_data(glm::uint64 pos, glm::uint64 size, const void* data) {
		use();
		glBufferSubData(GL_UNIFORM_BUFFER, pos, size, data);
	}
 
	void GlobalBuffer::activate_slot(glm::uint32 slot) {
		glBindBufferBase(GL_UNIFORM_BUFFER, slot, buffer_id);
	}

	void GlobalBuffer::set_range(glm::uint32 slot, glm::uint64 pos, glm::uint64 size) {
		glBindBufferRange(GL_UNIFORM_BUFFER, slot, buffer_id, pos, size);
	}
}