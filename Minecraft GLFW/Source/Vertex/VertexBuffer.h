#pragma once

class VertexBuffer {
private:
	unsigned int mID;
public:
	VertexBuffer(float* data, unsigned int vertexCount);
	VertexBuffer();
	~VertexBuffer();

	void Construct(float* data, unsigned int vertexCount);

	void Bind();
	void Unbind();
	void Delete();
};

