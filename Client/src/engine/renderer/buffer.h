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
		void set_data(glm::uint64 size, T* data, BufferType usage) {
			static_cast<SubClass*>(this)->new_data(size * sizeof(T), data, usage);
		}

		template<class T>
		void modify_data(glm::uint64 pos, glm::uint64 size, T* data) {
			static_cast<SubClass*>(this)->sub_data(pos * sizeof(T), size * sizeof(T), data + pos);
		}
	};

	class ArrayBuffer : public Buffer<ArrayBuffer> {
		friend class Buffer;

	private:
		void new_data(glm::uint64 size, const void* data, BufferType usage);

		void sub_data(glm::uint64 pos, glm::uint64 size, const void* data);

	public:
		void use();
	};

	class ElementBuffer : public Buffer<ElementBuffer> {
		friend class Buffer;

	private:
		void new_data(glm::uint64 size, const void* data, BufferType usage);

		void sub_data(glm::uint64 pos, glm::uint64 size, const void* data);

	public:
		void use();
	};

	class GlobalBuffer : public Buffer<GlobalBuffer> {
		friend class Buffer;

	private:
		void new_data(glm::uint64 size, const void* data, BufferType usage);

		void sub_data(glm::uint64 pos, glm::uint64 size, const void* data);

	public:
		void use();

		void activate_slot(glm::uint32 slot);

		void set_range(glm::uint32 slot, glm::uint64 pos, glm::uint64 size);
	};
}