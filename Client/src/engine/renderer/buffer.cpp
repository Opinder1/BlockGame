#include "buffer.h"

namespace engine {
	Buffer::Buffer(uint32 type) : buffer_type(type) {
		glGenBuffers(1, &buffer_id);
		bind();
	}

	Buffer::~Buffer() {
		glDeleteBuffers(1, &buffer_id);
	}

	void Buffer::bind() {
		glBindBuffer(buffer_type, buffer_id);
	}

	const uint32 Buffer::get_size() {
		return buffer_size;
	}
}