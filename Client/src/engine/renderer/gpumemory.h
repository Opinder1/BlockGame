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

	class GPUBuffer {
	private:
		uint32 buffer_id;
		uint32 buffer_type;

		void bind() {
			glBindBuffer(buffer_type, buffer_id);
		}

	public:
		GPUBuffer(const GPUBuffer& buffer) = delete;

		GPUBuffer(uint32 type) : buffer_type(type) {
			glGenBuffers(1, &buffer_id);
		}

		~GPUBuffer() {
			glDeleteBuffers(1, &buffer_id);
		}

		template<class Type>
		void type(uint32 index) {
			constexpr GLenum data_type = gl_type<Type>();

			bind();
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, 1, data_type, GL_FALSE, sizeof(Type), 0);
		}

		template<class Type>
		void type_vec(uint32 index) {
			constexpr int32 size = Type::length();
			constexpr GLenum data_type = gl_type<Type::value_type>();

			bind();
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, size, data_type, GL_FALSE, sizeof(Type), 0);
		}

		template<class Type>
		void type_mat(uint32 index) {
			constexpr int32 sizex = Type::row_type::length();
			constexpr int32 sizey = Type::col_type::length();
			constexpr GLenum data_type = gl_type<Type::value_type>();

			bind();
			for (int i = 0; i < sizey; i++) {
				glEnableVertexAttribArray(index + i);
				glVertexAttribPointer(index + i, sizex, data_type, GL_FALSE, sizex * sizey * sizeof(Type::value_type), (void*)(i * sizey * sizeof(Type::value_type)));
			}
		}

		void divisor(uint32 index, uint32 divisor) {
			bind();
			glVertexAttribDivisor(index, divisor);
		}

		template<class Type>
		void divisor_mat(uint32 index, uint32 divisor) {
			constexpr int32 sizey = Type::col_type::length();

			bind();
			for (int i = 0; i < sizey; i++) {
				glVertexAttribDivisor(index + i, divisor);
			}
		}

		template<class Type>
		void data(size_t size, Type* data, uint32 method) {
			bind();
			glBufferData(buffer_type, size * sizeof(Type), data, method);
		}

		template<class Type>
		void sub_data(size_t pos, size_t size, Type* data) {
			bind();
			glBufferSubData(buffer_type, pos * sizeof(Type), size * sizeof(Type), data + pos);
		}
	};

	class GPUObject {
	private:
		uint32 vertex_array;

		void bind() {
			glBindVertexArray(vertex_array);
		}

	public:
		GPUObject(const GPUObject&) = delete;

		GPUObject() {
			glGenVertexArrays(1, &vertex_array);
			glBindVertexArray(vertex_array);
			bind();
		}

		~GPUObject() {
			glDeleteVertexArrays(1, &vertex_array);
		}

		void draw_one(GLenum type, size_t vertexes) {
			bind();
			glDrawArrays(type, 0, (uint32)vertexes);
		}

		void draw_instances(GLenum type, size_t vertexes, size_t instances) {
			bind();
			glDrawArraysInstanced(type, 0, (uint32)vertexes, (uint32)instances);
		}
	};
}