#pragma once

#include <vector>

#include "../../Vertex/VertexArray.h"
#include "../../Vertex/VertexBuffer.h"
#include "../../Vertex/IndexBuffer.h"

#include"../../Vertex/VertexLayout/Vertex4.h"

#include "../../Graphic/Texture.h"
#include "../../Graphic/Shader.h"

#define ATLAS_W 16
#define ATLAS_H 4
#define TEXTURE_SIZE 16

class GUIMesh
{
private:
	VertexArray VAO;
	VertexBuffer VBO;
	IndexBuffer IBO;

	Texture* textureAtlas;

	std::vector<Vertex4<float>> vertexArr;
	std::vector<unsigned int> indexArr;

public:
	GUIMesh(Texture* textureAtlas);
	~GUIMesh();

	void Draw(Shader* program);

	void Push(Vertex4<float>* vertices, unsigned int vCount, unsigned int* indices, unsigned int eCount);

	void UpdateMesh();

	void Clear();
};

