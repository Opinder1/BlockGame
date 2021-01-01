#pragma once

#include <ocode.h>

#include <GL/glew.h>
#include <GLM/glm.hpp>

namespace engine {
	class Buffer {
	private:
		uint32 buffer_id;
		uint32 buffer_type;

		void bind();

	public:
		Buffer(const Buffer& buffer) = delete;
		Buffer(uint32 type);
		~Buffer();

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
}