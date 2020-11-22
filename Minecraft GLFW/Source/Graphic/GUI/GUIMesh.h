#pragma once

#include <vector>

#include "../../Vertex/VertexArray.h"
#include "../../Vertex/VertexBuffer.h"
#include "../../Vertex/IndexBuffer.h"

#include"../../Vertex/VertexLayout/Vertex4.h"

#include "../../Graphic/Texture.h"
#include "../../Graphic/Shader.h"

class GUIMesh
{
private:
	VertexArray VAO;
	VertexBuffer VBO;
	IndexBuffer IBO;

	Texture* textureAtlas;

	float monitorScale;

	std::vector<Vertex4<float>> vertexArr;
	std::vector<unsigned int> indexArr;

public:
	GUIMesh(Texture* textureAtlas, float monitorScale);
	~GUIMesh();

	void Draw(Shader* program);

	void Push(Vertex4<float>* vertices, unsigned int vCount, unsigned int* indices, unsigned int eCount);

	void UpdateMesh();

	void Clear();

	float GetMonitorScale();
};

