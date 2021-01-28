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

	const uint32 Buffer::get_id() {
		return buffer_id;
	}

	const uint64 Buffer::get_size() {
		return buffer_size;
	}

	GlobalBuffer::GlobalBuffer(uint32 id) : Buffer(GL_UNIFORM_BUFFER) {
		glBindBufferBase(GL_UNIFORM_BUFFER, id, get_id());
	}
}