#pragma once
#include <GL/glew.h>

#include <vector>

#include "../Graphic/Texture.h"


#include "../Vertex/VertexArray.h"
#include "../Vertex/VertexBuffer.h"

class Mesh
{
private:
	VertexArray VAO;
	VertexBuffer VBO;
	unsigned int vCount;

	Texture* texture;
public:
	Mesh(float* vertices, unsigned int vCount, std::string filePath);
	~Mesh();

	void Draw();
};

