#include <GL/glew.h>

#include "IndexBuffer.h"
#include "../ErrorHandling.h"

IndexBuffer::IndexBuffer() : mID(0){
}

IndexBuffer::IndexBuffer(unsigned int* indices, unsigned int vCount) {
	GLCall(glGenBuffers(1, &mID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, vCount * sizeof(unsigned int), indices, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
	GLCall(glDeleteBuffers(1, &mID));
}

void IndexBuffer::Construct(unsigned int* indices, unsigned int vCount) {
	GLCall(glGenBuffers(1, &mID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, vCount * sizeof(unsigned int), indices, GL_STATIC_DRAW));
}

void IndexBuffer::Bind() {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID));
}

void IndexBuffer::Unbind() {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
