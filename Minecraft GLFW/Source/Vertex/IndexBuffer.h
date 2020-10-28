#pragma once
#include "GL/glew.h"
class IndexBuffer
{
private:
	unsigned int mRendererID;
	unsigned int mCount;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	IndexBuffer(const unsigned short int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const
	{
		return mCount;
	}
};