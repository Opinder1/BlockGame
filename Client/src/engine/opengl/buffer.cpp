#include "../renderer/buffer.h"

#include "opengl.h"

namespace engine {
	GLenum buffertype_index[] = { GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW };

	glm::uint32 current_buffer = 0;

	Buffer::Buffer(glm::uint32 type) : buffer_type(type), buffer_size(0) {
		glGenBuffers(1, &buffer_id);
	}

	Buffer::~Buffer() {
		glDeleteBuffers(1, &buffer_id);
	}

	void Buffer::use() {
		if (current_buffer != buffer_id) {
			glBindBuffer(buffer_type, buffer_id);
			current_buffer = buffer_id;
		}
	}

	void Buffer::new_data(glm::uint64 size, void* data, BufferType usage) {
		glBufferData(buffer_type, size, data, buffertype_index[(glm::uint32)usage]);
	}

	void Buffer::sub_data(glm::uint64 pos, glm::uint64 size, void* data) {
		glBufferSubData(buffer_type, pos, size, data);
	}

	const glm::uint32 Buffer::get_id() {
		return buffer_id;
	}

	const glm::uint64 Buffer::get_size() {
		return buffer_size;
	}

	ArrayBuffer::ArrayBuffer() : Buffer(GL_ARRAY_BUFFER) {

	}
	
	ElementBuffer::ElementBuffer() : Buffer(GL_ELEMENT_ARRAY_BUFFER) {

	}

	GlobalBuffer::GlobalBuffer() : Buffer(GL_UNIFORM_BUFFER) {
	}
 
	void GlobalBuffer::activate_slot(glm::uint32 slot) {
		glBindBufferBase(GL_UNIFORM_BUFFER, slot, get_id());
	}

	void GlobalBuffer::set_range(glm::uint32 slot, glm::uint64 pos, glm::uint64 size) {
		glBindBufferRange(GL_UNIFORM_BUFFER, slot, get_id(), pos, size);
	}
}