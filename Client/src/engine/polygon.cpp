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
	Polygon::Polygon() {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(NULL);
	}

	Polygon::~Polygon() {
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}

	void Polygon::draw() {
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);

	}
}