#pragma once

#include <ocode.h>

#include <GL/glew.h>
#include <GLM/glm.hpp>

namespace engine {
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
			bind();
		}

		~GPUBuffer() {
			glDeleteBuffers(1, &buffer_id);
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

	template<class T> constexpr GLenum gl_type() = delete;

	template<> constexpr GLenum gl_type<int8>() { return GL_BYTE; }
	template<> constexpr GLenum gl_type<uint8>() { return GL_UNSIGNED_BYTE; }
	template<> constexpr GLenum gl_type<int16>() { return GL_SHORT; }
	template<> constexpr GLenum gl_type<uint16>() { return GL_UNSIGNED_SHORT; }
	template<> constexpr GLenum gl_type<int32>() { return GL_INT; }
	template<> constexpr GLenum gl_type<uint32>() { return GL_UNSIGNED_INT; }
	template<> constexpr GLenum gl_type<float>() { return GL_FLOAT; }
	template<> constexpr GLenum gl_type<double>() { return GL_DOUBLE; }

	template<class Type, uint32 SizeX = 1, uint32 SizeY = 1, uint32 Divisor = 0>
	class GPUArrayBuffer : public GPUBuffer {
	public:
		GPUArrayBuffer(uint32 index) : GPUBuffer(GL_ARRAY_BUFFER) {
			for (int i = 0; i < SizeY; i++) {
				glEnableVertexAttribArray(index + i);
				glVertexAttribPointer(index + i, SizeX, gl_type<Type>(), GL_FALSE, SizeX * SizeY * sizeof(Type), (void*)(i * SizeY * sizeof(Type)));
				if (Divisor) {
					glVertexAttribDivisor(index + i, Divisor);
				}
			}
		}
	};
}