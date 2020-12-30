#pragma once

#include <ocode.h>

#include <vector>

#include <GL/glew.h>
#include <GLM/glm.hpp>

namespace engine {
	template<uint32 buffer_count>
	class GPUMemory {
	private:
		uint32 vertex_array;

		uint32 vertex_buffers[buffer_count];

	public:
		GPUMemory(const GPUMemory&) = delete;
		GPUMemory() {
			glGenVertexArrays(1, &vertex_array);
			glBindVertexArray(vertex_array);

			glGenBuffers(buffer_count, vertex_buffers);
		}

		~GPUMemory() {
			glDeleteBuffers(buffer_count, vertex_buffers);
			glDeleteVertexArrays(1, &vertex_array);
		}

		void bind() {
			glBindVertexArray(vertex_array);
		}

		void bind_buffer(uint32 type, uint32 index) {
			glBindBuffer(type, vertex_buffers[index]);
		}

		template<class Type>
		void buffer_data(GLenum type, size_t data_size, Type* data, uint32 method) {
			glBufferData(type, sizeof(Type) * data_size, data, method);
		}

		template<class Type>
		void buffer_sub_data(GLenum type, size_t pos, size_t size, Type* data) {
			glBufferSubData(type, sizeof(Type) * pos, sizeof(Type) * size, data + pos);
		}

		template<class Type>
		void buffer_type(uint32 index, GLenum type) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, 1, type, GL_FALSE, sizeof(Type), 0);
		}

		template<class Type, uint32 Size>
		void buffer_type_vec(uint32 index, GLenum type) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, Size, type, GL_FALSE, Size * sizeof(Type), 0);
		}

		template<class Type, uint32 SizeX, uint32 SizeY>
		void buffer_type_mat(uint32 index, GLenum type) {
			for (int i = 0; i < SizeY; i++) {
				glEnableVertexAttribArray(index + i);
				glVertexAttribPointer(index + i, SizeX, type, GL_FALSE, SizeX * SizeY * sizeof(Type), (void*)(i * SizeX * sizeof(Type)));
			}
		}

		template<class Type>
		void buffer_divisor(uint32 index, uint32 divisor) {
			glVertexAttribDivisor(index, divisor);
		}

		template<class Type, uint32 Size>
		void buffer_divisor_vec(uint32 index, uint32 divisor) {
			glVertexAttribDivisor(index, divisor);
		}

		template<class Type, uint32 SizeX, uint32 SizeY>
		void buffer_divisor_mat(uint32 index, uint32 divisor) {
			for (int i = 0; i < SizeY; i++) {
				glVertexAttribDivisor(index + i, divisor);
			}
		}

		void draw_one(GLenum type, size_t vertexes) {
			glDrawArrays(type, 0, (uint32)vertexes);
		}

		void draw_instances(GLenum type, size_t vertexes, size_t instances) {
			glDrawArraysInstanced(type, 0, (uint32)vertexes, (uint32)instances);
		}
	};
}