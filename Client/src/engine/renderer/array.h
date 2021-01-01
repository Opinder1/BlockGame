#pragma once

#include <ocode.h>

#include <GL/glew.h>
#include <GLM/glm.hpp>

#include "buffer.h"

namespace engine {
	// Function to convert template type into opengl type constant at compile time
	template<class T> constexpr GLenum gl_type() = delete;

	template<> constexpr GLenum gl_type<int8>() { return GL_BYTE; }
	template<> constexpr GLenum gl_type<uint8>() { return GL_UNSIGNED_BYTE; }
	template<> constexpr GLenum gl_type<int16>() { return GL_SHORT; }
	template<> constexpr GLenum gl_type<uint16>() { return GL_UNSIGNED_SHORT; }
	template<> constexpr GLenum gl_type<int32>() { return GL_INT; }
	template<> constexpr GLenum gl_type<uint32>() { return GL_UNSIGNED_INT; }
	template<> constexpr GLenum gl_type<float>() { return GL_FLOAT; }
	template<> constexpr GLenum gl_type<double>() { return GL_DOUBLE; }

	class Array {
	private:
		uint32 vertex_array_id;

		void bind();

	public:
		Array(const Array&) = delete;
		Array();
		~Array();

		void draw(GLenum type, size_t vertexes);
		void draw_elements(GLenum type, size_t elements);

		void draw_instanced(GLenum type, size_t vertexes, size_t instances);
		void draw_elements_instanced(GLenum type, size_t elements, size_t instances);
	};

	// Array buffer object wrapper that can handle vectors, matricies and divisors
	template<class Type, uint32 SizeX = 1, uint32 SizeY = 1, uint32 Divisor = 0>
	class ArrayBuffer : public Buffer {
	public:
		ArrayBuffer(uint32 index) : Buffer(GL_ARRAY_BUFFER) {
			// If SizeY is 1 then optimiser will get rid of this loop
			for (int i = 0; i < SizeY; i++) {
				// Sets the format for the buffer using the index provided
				glEnableVertexAttribArray(index + i);
				glVertexAttribPointer(index + i, SizeX, gl_type<Type>(), GL_FALSE, SizeX * SizeY * sizeof(Type), (void*)(i * SizeY * sizeof(Type)));

				// If divisor is 0 then optimiser will get rid of this function
				if (Divisor) {
					glVertexAttribDivisor(index + i, Divisor);
				}
			}
		}
	};

	class ElementBuffer : public Buffer {
	public:
		ElementBuffer() : Buffer(GL_ELEMENT_ARRAY_BUFFER) {

		}
	};
}