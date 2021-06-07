#include "../gl/buffer.h"

#include "opengl.h"

namespace engine {
	glm::uint32 current_array_buffer = 0;
	glm::uint32 current_element_buffer = 0;
	glm::uint32 current_uniform_buffer = 0;
	glm::uint32 current_global_buffer = 0;

	int SharedBuffer::max_slots = 0;
	int SharedBuffer::max_size = 0;

	int GlobalBuffer::max_size = 0;
	int GlobalBuffer::max_slots = 0;

	void init_buffer_limits() {
		glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, (GLint*)&SharedBuffer::max_size);
		glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, (GLint*)&SharedBuffer::max_slots);
		glGetIntegerv(GL_MAX_SHADER_STORAGE_BLOCK_SIZE, (GLint*)&GlobalBuffer::max_size);
		glGetIntegerv(GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS, (GLint*)&GlobalBuffer::max_slots);
	}

	void BufferBase::_new() {
		glGenBuffers(1, &buffer_id);
	}

	void BufferBase::_delete() {
		glDeleteBuffers(1, &buffer_id);
	}

	void ArrayBuffer::use() {
		if (current_array_buffer != buffer_id) {
			glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
			current_array_buffer = buffer_id;
		}
	}

	void ArrayBuffer::create_data(glm::uint64 size, const void* data, BufferType usage) {
		use();
		glBufferData(GL_ARRAY_BUFFER, size, data, buffer_type(usage));
	}

	void ArrayBuffer::modify_data(glm::uint64 pos, glm::uint64 size, const void* data) {
		use();
		glBufferSubData(GL_ARRAY_BUFFER, pos, size, data);
	}

	void ElementBuffer::use() {
		if (current_element_buffer != buffer_id) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
			current_uniform_buffer = buffer_id;
		}
	}

	void ElementBuffer::create_data(glm::uint64 size, const void* data, BufferType usage) {
		use();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, buffer_type(usage));
	}

	void ElementBuffer::modify_data(glm::uint64 pos, glm::uint64 size, const void* data) {
		use();
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, pos, size, data);
	}

	void SharedBuffer::use() {
		if (current_uniform_buffer != buffer_id) {
			glBindBuffer(GL_UNIFORM_BUFFER, buffer_id);
			current_uniform_buffer = buffer_id;
		}
	}

	void SharedBuffer::create_data(glm::uint64 size, const void* data, BufferType usage) {
		use();
		glBufferData(GL_UNIFORM_BUFFER, size, data, buffer_type(usage));
	}

	void SharedBuffer::modify_data(glm::uint64 pos, glm::uint64 size, const void* data) {
		use();
		glBufferSubData(GL_UNIFORM_BUFFER, pos, size, data);
	}
 
	void SharedBuffer::activate_slot(glm::uint32 slot) {
		glBindBufferBase(GL_UNIFORM_BUFFER, slot, buffer_id);
	}

	void SharedBuffer::set_range(glm::uint32 slot, glm::uint64 pos, glm::uint64 size) {
		glBindBufferRange(GL_UNIFORM_BUFFER, slot, buffer_id, pos, size);
	}

	void GlobalBuffer::use() {
		if (current_global_buffer != buffer_id) {
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer_id);
			current_global_buffer = buffer_id;
		}
	}

	void GlobalBuffer::create_data(glm::uint64 size, const void* data, BufferType usage) {
		use();
		glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, buffer_type(usage));
	}

	void GlobalBuffer::modify_data(glm::uint64 pos, glm::uint64 size, const void* data) {
		use();
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, pos, size, data);
	}

	void GlobalBuffer::activate_slot(glm::uint32 slot) {
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, slot, buffer_id);
	}

	void GlobalBuffer::set_range(glm::uint32 slot, glm::uint64 pos, glm::uint64 size) {
		glBindBufferRange(GL_SHADER_STORAGE_BUFFER, slot, buffer_id, pos, size);
	}
}