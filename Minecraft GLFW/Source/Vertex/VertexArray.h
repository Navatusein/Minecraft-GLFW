#pragma once
#include "VertexBuffer.h"

class VertexArray {
private:
	unsigned int mID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer& VBO);

	void Bind();
	void Unbind();
};

