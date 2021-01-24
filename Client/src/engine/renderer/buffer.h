#pragma once

#include <ocode.h>

#include <vector>

#include "opengl.h"
#include "texture.h"

namespace engine {
	class Buffer {
	private:
		uint32 buffer_id;
		uint32 buffer_type; // Can probally be worked out at compile time unless buffers can change type
		uint32 buffer_size;

	protected:
		// Wrapper around opengl binding function
		void bind();

		// Get read only id for buffer subclass
		const uint32 get_id();

	public:
		// Opengl object should not be copied or moved, only pointed to
		Buffer(const Buffer&) = delete;
		Buffer(uint32 type);
		~Buffer();

		// Get the size of the buffer last set using data()
		const uint32 get_size();

		// Allocate buffer memory and fill it
		template<class Type>
		void data(uint32 size, Type* data, BufferType usage) {
			bind();
			buffer_size = size;
			glBufferData(buffer_type, size * sizeof(Type), data, (GLenum)usage);
		}

		// Update section of buffer with new data
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

		// Set the buffer layout for array attribute
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

	template<class T>
	class InstanceBuffer : private ArrayBuffer {
	private:
		std::vector<T> instances;

	public:
		template<class Type, uint32 SizeX = 1, uint32 SizeY = 1, uint32 Divisor = 0>
		void format(uint32 index) {
			ArrayBuffer::format<Type, SizeX, SizeY, Divisor>(index);
		}

		uint32 new_instance(const T& value) {
			size_t size = instances.capacity();
			instances.push_back(value);

			if (instances.capacity() != size) {
				data((uint32)instances.capacity(), instances.data(), BufferType::DYNAMIC);
			}
			else {
				sub_data((uint32)instances.size() - 1, 1, instances.data());
			}

			return (uint32)instances.size() - 1;
		}

		void delete_instance(uint32 index){
			size_t size = instances.capacity();

			instances.erase(instances.begin() + index);

			sub_data(index, (uint32)instances.size() - index, instances.data());
		}

		void update_instance(uint32 index, const T& value) {
			instances.at(index) = value;

			sub_data(index, 1, instances.data());
		}

		uint32 instance_count() {
			return (uint32)instances.size();
		}
	};

	// Element buffer object wrapper that can handle element datatype
	class ElementBuffer : public Buffer {
	protected:
		GLenum element_type;

	public:
		ElementBuffer() : Buffer(GL_ELEMENT_ARRAY_BUFFER), element_type(GL_UNSIGNED_INT) {}

		// Overriding data method to also update element type
		template<class Type>
		void data(uint32 size, Type* data, BufferType usage) {
			element_type = gl_type<Type>();

			Buffer::data(size, data, usage);
		}
	};

	// Global buffer object wrapper for creating global uniform groups for all shaders
	class GlobalBuffer : public Buffer {
	public:
		GlobalBuffer(uint32 id);
	};

	class TextureBuffer {
	private:
		uint32 buffer_id;

	public:
		TextureBuffer(const TextureBuffer&) = delete;
		TextureBuffer();
		~TextureBuffer();

		void bind();
		void use(uint32 index);

		void data(const Texture& texture);
	};
}