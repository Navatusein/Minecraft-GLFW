#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
	unsigned int mRendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vbo, const VBLayout& layout);

	void Bind() const;
	void Unbind() const;
};

