#include <GL/glew.h>
#include <iostream>;

#include "VertexBuffer.h"
#include "../ErrorHandling.h"

VertexBuffer::VertexBuffer(float* data, unsigned int vertexCount) : mID(0) {
	GLCall(glGenBuffers(1, &mID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, mID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, 5 * (int)vertexCount * sizeof(float) , data, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer() : mID(0){
}

VertexBuffer::~VertexBuffer() {
	GLCall(glDeleteBuffers(1, &mID));
}

void VertexBuffer::Construct(float* data, unsigned int vertexCount) {
	GLCall(glGenBuffers(1, &mID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, mID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, 5 * (int)vertexCount * sizeof(float), data, GL_STATIC_DRAW));
}

void VertexBuffer::Bind() {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, mID));
}

void VertexBuffer::Unbind() {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
