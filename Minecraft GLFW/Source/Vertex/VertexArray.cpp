#include <GL/glew.h>

#include "VertexArray.h"

VertexArray::VertexArray() : mID(0) {
	glGenVertexArrays(1, &mID);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &mID);
}

void VertexArray::AddBuffer(VertexBuffer VBO) {
	Bind();
	VBO.Bind();

	for(int i = 0; i < 2; i++) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}
}

void VertexArray::Bind() {
	glBindVertexArray(mID);
}

void VertexArray::Unbind() {
	glBindVertexArray(0);
}
