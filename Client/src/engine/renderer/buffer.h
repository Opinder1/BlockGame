#pragma once

#include <ocode.h>

#include <vector>

#include "gl.h"

namespace engine {
	enum class BufferType : glm::uint32 {
		Static,
		Dynamic,
		Stream
	};

	class Buffer {
	private:
		glm::uint32 buffer_id;
		glm::uint32 buffer_type;
		glm::uint64 buffer_size;

	protected:
		// Wrapper around opengl binding function
		void use();

		// Get read only id for buffer subclass
		const glm::uint32 get_id();

		// Allocate buffer memory and fill it
		void new_data(glm::uint64 size, void* data, BufferType usage);

		// Update section of buffer with new data
		void sub_data(glm::uint64 pos, glm::uint64 size, void* data);

	public:
		// Opengl object should not be copied or moved, only pointed to
		Buffer(const Buffer&) = delete;
		Buffer(glm::uint32 type);
		~Buffer();

		// Get the size of the buffer last set using data()
		const glm::uint64 get_size();

		// Memory allocation wrapper
		template<class T>
		void set_data(glm::uint64 size, T* data, BufferType usage) {
			use();
			buffer_size = size;
			new_data(size * sizeof(T), data, usage);
		}

		// Memory modification wrapper
		template<class T>
		void modify_data(glm::uint64 pos, glm::uint64 size, T* data) {
			use();
			sub_data(pos * sizeof(T), size * sizeof(T), data + pos);
		}
	};

	// Array buffer object wrapper that can handle vectors, matricies and divisors
	class ArrayBuffer : public Buffer {
		friend class Array;

	public:
		ArrayBuffer();
	};

	// Element buffer object wrapper that can handle element datatype
	class ElementBuffer : public Buffer {
	public:
		ElementBuffer();
	};

	template<class T>
	class InstanceBuffer : private ArrayBuffer {
	private:
		std::vector<T> instances;

	public:
		template<class Type, glm::uint32 SizeX = 1, glm::uint32 SizeY = 1, glm::uint32 Divisor = 0>
		void format(glm::uint32 index) {
			ArrayBuffer::format<Type, SizeX, SizeY, Divisor>(index);
		}

		glm::uint32 new_instance(const T& value) {
			size_t size = instances.capacity();
			instances.push_back(value);

			if (instances.capacity() != size) {
				set_data((glm::uint32)instances.capacity(), instances.data(), BufferType::Dynamic);
			}
			else {
				modify_data((glm::uint32)instances.size() - 1, 1, instances.data());
			}

			return (glm::uint32)instances.size() - 1;
		}

		void delete_instance(glm::uint32 index){
			size_t size = instances.capacity();

			instances.erase(instances.begin() + index);

			modify_data(index, (glm::uint32)instances.size() - index, instances.data());
		}

		void update_instance(glm::uint32 index, const T& value) {
			instances.at(index) = value;

			modify_data(index, 1, instances.data());
		}

		glm::uint32 instance_count() {
			return (glm::uint32)instances.size();
		}
	};

	// Global buffer object wrapper for creating global uniform groups for all shaders
	class GlobalBuffer : public Buffer {
	public:
		GlobalBuffer();

		void activate_slot(glm::uint32 slot);
		void set_range(glm::uint32 slot, glm::uint64 pos, glm::uint64 size);
	};
}