#pragma once

#include <ocode.h>

#include "gl.h"
#include "buffer.h"

namespace engine {
	enum class DrawType {
		Default,
		Strip,
		Fan
	};

	class Array {
	private:
		glm::uint32 vertex_array_id;

	protected:
		void use();

	public:
		Array(const Array&) = delete;
		Array();
		~Array();

		void set_attribute(glm::uint32 pos, ArrayBuffer& buffer, Type type, glm::uint32 width = 1, glm::uint32 height = 1, glm::uint32 divisor = 0);

		void draw(DrawType type, glm::uint32 vertexes);
		void draw_instanced(DrawType type, glm::uint32 vertexes, glm::uint32 instances);
	};

	class ElementArray : public Array, public ElementBuffer {
	private:
		Type element_type;

	public:
		ElementArray(Type type) : Array(), ElementBuffer(), element_type(type) {}

		void draw(glm::uint32 elements);
		void draw_instanced(glm::uint32 elements, glm::uint32 instances);
	};
}