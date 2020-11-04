#pragma once
class IndexBuffer
{
private:
	unsigned int mID;
public:
	IndexBuffer();
	IndexBuffer(unsigned int* indices, unsigned int vCount);
	~IndexBuffer();

	void Construct(unsigned int* indices, unsigned int vCount);

	void Bind();
	void Unbind();
};

