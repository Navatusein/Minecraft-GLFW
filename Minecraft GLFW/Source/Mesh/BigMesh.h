#pragma once
#include <vector>

#include "../Graphic/Shader.h"
#include "../Graphic/Texture.h"

#include "../Vertex/VertexArray.h"
#include "../Vertex/VertexBuffer.h"
#include "../Vertex/IndexBuffer.h"

class BigMesh
{
private:
	std::vector<float> vertexArr;
	std::vector<unsigned int> indicesArr;
	Texture* textureAtlas;
	VertexArray VAO;
	VertexBuffer VBO;
	IndexBuffer IBO;
public:
	BigMesh(Texture* tex);
	~BigMesh();

	void Draw(Shader* program);
	void Update();

	void Clear();

	void Push(float* vertices, unsigned int vCount, unsigned int* indices, unsigned int eCount);
	
};

