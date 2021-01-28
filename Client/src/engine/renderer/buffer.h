#pragma once

#include <ocode.h>

#include <vector>

#include "opengl.h"

namespace engine {
	class Buffer {
	private:
		uint32 buffer_id;
		uint32 buffer_type;
		uint64 buffer_size;

	protected:
		// Wrapper around opengl binding function
		void use();

		// Get read only id for buffer subclass
		const uint32 get_id();

	public:
		// Opengl object should not be copied or moved, only pointed to
		Buffer(const Buffer&) = delete;
		Buffer(uint32 type);
		~Buffer();

		// Get the size of the buffer last set using data()
		const uint64 get_size();

		// Allocate buffer memory and fill it
		template<class T>
		void data(uint64 size, T* data, BufferType usage) {
			use();
			buffer_size = size;
			glBufferData(buffer_type, size * sizeof(T), data, (GLenum)usage);
		}

		// Update section of buffer with new data
		template<class T>
		void sub_data(uint64 pos, uint64 size, T* data) {
			use();
			glBufferSubData(buffer_type, pos * sizeof(T), size * sizeof(T), data + pos);
		}
	};

	// Array buffer object wrapper that can handle vectors, matricies and divisors
	class ArrayBuffer : public Buffer {
		friend class Array;

	public:
		ArrayBuffer() : Buffer(GL_ARRAY_BUFFER) {}
	};

	// Element buffer object wrapper that can handle element datatype
	class ElementBuffer : public Buffer {
	public:
		ElementBuffer() : Buffer(GL_ELEMENT_ARRAY_BUFFER) {}
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
				data((uint32)instances.capacity(), instances.data(), BufferType::Dynamic);
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

	// Global buffer object wrapper for creating global uniform groups for all shaders
	class GlobalBuffer : public Buffer {
	public:
		GlobalBuffer(uint32 id);
	};
}