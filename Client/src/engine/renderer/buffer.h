#pragma once

#include <ocode.h>

#include "gl.h"

namespace engine {
	class BufferBase {
	protected:
		glm::uint32 buffer_id;

	public:
		void _new();
		void _delete();
	};

	template<class SubClass>
	class Buffer : public BufferBase {
	public:
		template<class T>
		void create(glm::uint64 size, T* data, BufferType usage) {
			static_cast<SubClass*>(this)->create_data(size * sizeof(T), data, usage);
		}

		template<class T>
		void modify(glm::uint64 pos, glm::uint64 size, T* data) {
			static_cast<SubClass*>(this)->modify_data(pos * sizeof(T), size * sizeof(T), data);
		}
	};

	class ArrayBuffer : public Buffer<ArrayBuffer> {
		friend class Array;

	private:
		void use();

	public:
		void create_data(glm::uint64 size, const void* data, BufferType usage);

		void modify_data(glm::uint64 pos, glm::uint64 size, const void* data);
	};

	class ElementBuffer : public Buffer<ElementBuffer> {
		friend class ElementArray;

	private:
		void use();

	public:
		void create_data(glm::uint64 size, const void* data, BufferType usage);

		void modify_data(glm::uint64 pos, glm::uint64 size, const void* data);
	};

	class SharedBuffer : public Buffer<SharedBuffer> {
	public:
		static int max_slots;
		static int max_size;

	private:
		void use();

	public:
		void create_data(glm::uint64 size, const void* data, BufferType usage);

		void modify_data(glm::uint64 pos, glm::uint64 size, const void* data);

		void activate_slot(glm::uint32 slot);

		void set_range(glm::uint32 slot, glm::uint64 pos, glm::uint64 size);
	};

	class GlobalBuffer : public Buffer<GlobalBuffer> {
	public:
		static int max_slots;
		static int max_size;

	private:
		void use();

	public:
		void create_data(glm::uint64 size, const void* data, BufferType usage);

		void modify_data(glm::uint64 pos, glm::uint64 size, const void* data);

		// TODO Implement
		void activate_slot(glm::uint32 slot);

		void set_range(glm::uint32 slot, glm::uint64 pos, glm::uint64 size);
	};
}