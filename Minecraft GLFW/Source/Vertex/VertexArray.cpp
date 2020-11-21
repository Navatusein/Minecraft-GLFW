#include <GL/glew.h>

#include "VertexArray.h"
#include "../ErrorHandling.h"

VertexArray::VertexArray() : mID(0) {
	glGenVertexArrays(1, &mID);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &mID);
}

void VertexArray::AddBuffer(VertexBuffer& VBO) {
	Bind();
	VBO.Bind();

	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat))));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))));
	GLCall(glEnableVertexAttribArray(1));
}

void VertexArray::AddBuffer2d(VertexBuffer& VBO) {
	Bind();
	VBO.Bind();

	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat))));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat))));
	GLCall(glEnableVertexAttribArray(1));
}

void VertexArray::Bind() {
	GLCall(glBindVertexArray(mID));
}

void VertexArray::Unbind() {
	GLCall(glBindVertexArray(0));
}
