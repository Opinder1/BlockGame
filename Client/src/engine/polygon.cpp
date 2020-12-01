#include "polygon.h"

float square[] = {
	0.5f, -0.5f,
	-0.5f, 0.5f,
	-0.5f, -0.5f,

	0.5f, -0.5f,
	-0.5f, 0.5f,
	0.5f, 0.5f
};

namespace engine {
	Polygon::Polygon() : Polygon(square) {
	
	}

	Polygon::Polygon(float* data) {
		glGenVertexArrays(1, &vertex_array_id);
		glBindVertexArray(vertex_array_id);

		glGenBuffers(1, &vertex_buffer_id);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

		int index = 0;

		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, 0, 0);

		unbind();
	}

	Polygon::~Polygon() {
		glDeleteBuffers(1, &vertex_buffer_id);
		glDeleteVertexArrays(1, &vertex_array_id);
	}

	void Polygon::draw() {
		glBindVertexArray(vertex_array_id);
		glDrawArrays(GL_TRIANGLES, 0, 6);

	}

	void Polygon::unbind() {
		glBindVertexArray(NULL);
	}
}