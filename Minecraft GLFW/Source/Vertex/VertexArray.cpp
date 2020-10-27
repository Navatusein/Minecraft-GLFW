#include <GL/glew.h>

#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &mRendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &mRendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vbo, const VBLayout& layout)
{
	Bind();
	vbo.Bind();
	const auto& elements = layout.GetElements();

	unsigned int offset = 0;
	for(unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * VBLayout::Element::GetTypeSize(element.type);
	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(mRendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
