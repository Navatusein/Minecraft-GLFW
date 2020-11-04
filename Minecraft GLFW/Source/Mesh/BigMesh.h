#pragma once
#include <vector>

#include "../Graphic/Shader.h"
#include "../Graphic/Texture.h"

#include "../Vertex/VertexArray.h"
#include "../Vertex/VertexBuffer.h"

class BigMesh
{
private:
	std::vector<float> vertexArr;
	Texture* textureAtlas;
public:
	BigMesh(Texture* tex);
	~BigMesh();

	void Draw(Shader* program);

	void Push(float* vertices, unsigned int vCount);
	
};

