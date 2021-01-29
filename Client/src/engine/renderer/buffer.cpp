#include "buffer.h"

namespace engine {
	uint32 current_buffer = 0;

	Buffer::Buffer(uint32 type) : buffer_type(type), buffer_size(0) {
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

	void Buffer::new_data(uint64 size, void* data, BufferType usage) {
		glBufferData(buffer_type, size, data, (GLenum)usage);
	}

	void Buffer::sub_data(uint64 pos, uint64 size, void* data) {
		glBufferSubData(buffer_type, pos, size, data);
	}

	const uint32 Buffer::get_id() {
		return buffer_id;
	}

	const uint64 Buffer::get_size() {
		return buffer_size;
	}

	ArrayBuffer::ArrayBuffer() : Buffer(GL_ARRAY_BUFFER) {

	}
	
	ElementBuffer::ElementBuffer() : Buffer(GL_ELEMENT_ARRAY_BUFFER) {

	}

	GlobalBuffer::GlobalBuffer(uint32 slot) : Buffer(GL_UNIFORM_BUFFER) {
		glBindBufferBase(GL_UNIFORM_BUFFER, slot, get_id());
	}

	void GlobalBuffer::activate_slot(uint32 slot) {
		glBindBufferBase(GL_UNIFORM_BUFFER, slot, get_id());
	}
}