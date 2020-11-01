#include <GL/glew.h>

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(float* data, unsigned int vertexCount) : mID(0) {
	glGenBuffers(1, &mID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, 5 * sizeof(data) * vertexCount, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &mID);
}

void VertexBuffer::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, mID);
}

void VertexBuffer::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
