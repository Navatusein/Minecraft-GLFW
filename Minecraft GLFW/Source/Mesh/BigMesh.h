#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "../Graphic/Shader.h"
#include "../Graphic/Texture.h"

#include "../Vertex/VertexArray.h"
#include "../Vertex/VertexBuffer.h"
#include "../Vertex/IndexBuffer.h"

#define postype unsigned short int

#define ATLAS_W 16
#define ATLAS_H 4
#define TEXTURE_SIZE 16

class BigMesh
{
private:
	float* vertexArr;
	unsigned int* indexArr;

	unsigned int vCount;
	unsigned int eCount;

	unsigned int max_vCount;
	unsigned int max_eCount;

	Texture* textureAtlas;

	VertexArray VAO;
	VertexBuffer VBO;
	IndexBuffer IBO;

	glm::mat4 transform;
public:
	BigMesh();
	BigMesh(unsigned int max_vCount, unsigned int max_eCount, Texture* tex);
	~BigMesh();

	void Construct(unsigned int max_vCount, unsigned int max_eCount, Texture* tex);

	void UpdateMesh();

	void Draw(Shader* program);

	void Clear();

	void Move(float x, float y, float z);

	void Center();

	void Push(float* vertices, unsigned int vCount, unsigned int* indices, unsigned int eCount);

};

