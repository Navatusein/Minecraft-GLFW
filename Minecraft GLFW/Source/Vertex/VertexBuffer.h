#pragma once

class VertexBuffer {
private:
	unsigned int mID;
public:
	VertexBuffer(float* data, unsigned int vertexCount);
	~VertexBuffer();

	void Bind();
	void Unbind();
};

