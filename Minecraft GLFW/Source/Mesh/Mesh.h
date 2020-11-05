#pragma once
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <vector>

#include "../Graphic/Texture.h"

#include "../Vertex/VertexArray.h"
#include "../Vertex/VertexBuffer.h"
#include "../Vertex/IndexBuffer.h"

#include "../Graphic/Shader.h"

class Mesh
{
private:
	VertexArray VAO;
	VertexBuffer VBO;
	IndexBuffer IBO;
	unsigned int vCount;

	glm::mat4 transform;

	Texture* texture;
public:
	Mesh();
	Mesh(float* vertices, unsigned int* indices, unsigned int vCount, Texture* tex);
	~Mesh();

	void Construct(float* vertices, unsigned int* indices, unsigned int vCount, Texture* tex);

	void Rotate(float x, float y, float z);
	void Scale(float x, float y, float z);
	void Move(float x, float y, float z);

	void Center();

	void Draw(Shader* program);
};

