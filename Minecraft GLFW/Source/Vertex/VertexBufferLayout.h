#pragma once

#include <vector>
#include <GL/glew.h>

/*vertex buffer layout*/
class VBLayout
{
public:
	struct Element
	{
		unsigned int type;
		unsigned int count;
		unsigned char normalized;

		static unsigned int GetTypeSize(unsigned int type)
		{
			switch(type)
			{
				case GL_FLOAT: return 4;
				case GL_UNSIGNED_INT: return 4;
				case GL_UNSIGNED_SHORT: return 2;
				case GL_UNSIGNED_BYTE: return 1;
			}
			return 0;
		}
	};
private:
	std::vector<Element> mElements;
	unsigned int mStride;
public:
	VBLayout() : mStride(0)
	{
	}

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		mElements.push_back({ GL_FLOAT, count, GL_FALSE });
		mStride += count * Element::GetTypeSize(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		mElements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		mStride += count * Element::GetTypeSize(GL_UNSIGNED_INT);
	}

	template<>
	void Push <unsigned short int>(unsigned int count)
	{
		mElements.push_back({ GL_UNSIGNED_SHORT, count, GL_FALSE });
		mStride += count * Element::GetTypeSize(GL_UNSIGNED_SHORT);
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		mElements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		mStride += count * Element::GetTypeSize(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<Element> GetElements() const&
	{
		return mElements;
	}
	inline unsigned int GetStride() const
	{
		return mStride;
	}
};