#pragma once

#include <ocode.h>

#include <GL/glew.h>
#include <GLM/glm.hpp>

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

	enum class BufferType : uint32 {
		STATIC = GL_STATIC_DRAW,
		DYNAMIC = GL_DYNAMIC_DRAW,
		STREAM = GL_STREAM_DRAW
	};

	struct DrawElementsIndirectCommand {
		uint32  count;
		uint32  primCount;
		uint32  firstIndex;
		uint32  baseVertex;
		uint32  baseInstance;
	};

	class Buffer {
	private:
		uint32 buffer_id;
		uint32 buffer_type; // Can probally be worked out at compile time unless buffers can change type

		uint32 buffer_size;

	protected:
		void bind();

	public:
		Buffer(const Buffer&) = delete;
		Buffer(uint32 type);
		~Buffer();

		const uint32 get_size();

		template<class Type>
		void data(uint32 size, Type* data, BufferType method) {
			bind();
			buffer_size = size;
			glBufferData(buffer_type, size * sizeof(Type), data, (GLenum)method);
		}

		template<class Type>
		void sub_data(uint32 pos, uint32 size, Type* data) {
			bind();
			glBufferSubData(buffer_type, pos * sizeof(Type), size * sizeof(Type), data + pos);
		}
	};

	// Array buffer object wrapper that can handle vectors, matricies and divisors
	class ArrayBuffer : public Buffer {
	public:
		ArrayBuffer() : Buffer(GL_ARRAY_BUFFER) {}

		template<class Type, uint32 SizeX = 1, uint32 SizeY = 1, uint32 Divisor = 0>
		void format(uint32 index) {
			bind();
			// If SizeY is 1 then optimiser will get rid of this loop
			for (int i = 0; i < SizeY; i++) {
				// Sets attribute at the index to array mode
				glEnableVertexAttribArray(index + i);
				// Sets the format for the attribute
				glVertexAttribPointer(index + i, SizeX, gl_type<Type>(), GL_FALSE, SizeX * SizeY * sizeof(Type), (void*)(i * SizeY * sizeof(Type)));

				// If divisor is 0 then optimiser will get rid of this function
				if (Divisor) {
					// Sets attribute index to only increment after [Divisor] instances
					glVertexAttribDivisor(index + i, Divisor);
				}
			}
		}
	};

	class ElementBuffer : public Buffer {
	protected:
		GLenum element_type;

	public:
		ElementBuffer() : Buffer(GL_ELEMENT_ARRAY_BUFFER), element_type(GL_UNSIGNED_INT) {}

		template<class Type>
		void data(uint32 size, Type* data, BufferType method) {
			element_type = gl_type<Type>();

			Buffer::data(size, data, method);
		}
	};

	class DrawCallBuffer : public Buffer {
	public:
		typedef DrawElementsIndirectCommand Command;

		DrawCallBuffer() : Buffer(GL_DRAW_INDIRECT_BUFFER) {}

		void data(uint32 size, Command* data, BufferType method);
		//Buffer::data(size, data, method);

		void sub_data(uint32 pos, uint32 size, Command* data);
		//Buffer::sub_data(pos, size, data);
	};
}