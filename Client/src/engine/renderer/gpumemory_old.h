#pragma once

#include <ocode.h>

#include <vector>

#include <GL/glew.h>
#include <GLM/glm.hpp>

namespace engine {
	template<class T> constexpr GLenum gl_type() { return 0; };

	template<> constexpr GLenum gl_type<int8>() { return GL_BYTE; }
	template<> constexpr GLenum gl_type<uint8>() { return GL_UNSIGNED_BYTE; }
	template<> constexpr GLenum gl_type<int16>() { return GL_SHORT; }
	template<> constexpr GLenum gl_type<uint16>() { return GL_UNSIGNED_SHORT; }
	template<> constexpr GLenum gl_type<int32>() { return GL_INT; }
	template<> constexpr GLenum gl_type<uint32>() { return GL_UNSIGNED_INT; }
	template<> constexpr GLenum gl_type<float>() { return GL_FLOAT; }
	template<> constexpr GLenum gl_type<double>() { return GL_DOUBLE; }

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
		void buffer_type(uint32 index) {
			constexpr GLenum type = gl_type<Type>();

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, 1, type, GL_FALSE, sizeof(Type), 0);
		}

		template<class Type>
		void buffer_type_vec(uint32 index) {
			constexpr int32 size = Type::length();
			constexpr GLenum type = gl_type<Type::value_type>();

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, size, type, GL_FALSE, sizeof(Type), 0);
		}

		template<class Type>
		void buffer_type_mat(uint32 index) {
			constexpr int32 sizex = Type::row_type::length();
			constexpr int32 sizey = Type::col_type::length();
			constexpr GLenum type = gl_type<Type::value_type>();

			for (int i = 0; i < sizey; i++) {
				glEnableVertexAttribArray(index + i);
				glVertexAttribPointer(index + i, sizex, type, GL_FALSE, sizex * sizey * sizeof(Type::value_type), (void*)(i * sizey * sizeof(Type::value_type)));
			}
		}

		void buffer_divisor(uint32 index, uint32 divisor) {
			glVertexAttribDivisor(index, divisor);
		}

		template<class Type>
		void buffer_divisor_mat(uint32 index, uint32 divisor) {
			constexpr int32 sizey = Type::col_type::length();

			for (int i = 0; i < sizey; i++) {
				glVertexAttribDivisor(index + i, divisor);
			}
		}

		template<class Type>
		void buffer_data(GLenum type, size_t data_size, Type* data, uint32 method) {
			glBufferData(type, data_size * sizeof(Type), data, method);
		}

		template<class Type>
		void buffer_sub_data(GLenum type, size_t pos, size_t size, Type* data) {
			glBufferSubData(type, pos * sizeof(Type), size * sizeof(Type), data + pos);
		}

		void draw_one(GLenum type, size_t vertexes) {
			glDrawArrays(type, 0, (uint32)vertexes);
		}

		void draw_instances(GLenum type, size_t vertexes, size_t instances) {
			glDrawArraysInstanced(type, 0, (uint32)vertexes, (uint32)instances);
		}
	};
}