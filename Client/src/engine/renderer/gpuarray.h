#pragma once

#include <ocode.h>

#include <GL/glew.h>
#include <GLM/glm.hpp>

namespace engine {
	class GPUArray {
	private:
		uint32 vertex_array_id;

		void bind() {
			glBindVertexArray(vertex_array_id);
		}

	public:
		GPUArray(const GPUArray&) = delete;

		GPUArray() {
			glGenVertexArrays(1, &vertex_array_id);
			bind();
		}

		~GPUArray() {
			glDeleteVertexArrays(1, &vertex_array_id);
		}

		void draw_one(GLenum type, size_t vertexes) {
			bind();
			glDrawArrays(type, 0, (uint32)vertexes);
		}

		void draw_instances(GLenum type, size_t vertexes, size_t instances) {
			bind();
			glDrawArraysInstanced(type, 0, (uint32)vertexes, (uint32)instances);
		}
	};
}