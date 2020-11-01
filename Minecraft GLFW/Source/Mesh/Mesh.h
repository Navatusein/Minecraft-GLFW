#pragma once
#include <GL/glew.h>

#include <vector>

#include "../Graphic/Textures.h"


#include "../Vertex/VertexArray.h"
#include "../Vertex/VertexBuffer.h"

class Mesh
{
private:
	VertexArray VAO;
	VertexBuffer VBO;
	unsigned int vCount;
public:
	Mesh(float* vertices, unsigned int vCount);
	~Mesh();

	void Draw();
};

