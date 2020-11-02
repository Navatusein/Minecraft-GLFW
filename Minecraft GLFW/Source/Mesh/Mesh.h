#pragma once
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <vector>

#include "../Graphic/Texture.h"


#include "../Vertex/VertexArray.h"
#include "../Vertex/VertexBuffer.h"

#include "../Graphic/Shader.h"

class Mesh
{
private:
	VertexArray VAO;
	VertexBuffer VBO;
	unsigned int vCount;

	glm::mat4 transform;

	Texture* texture;
public:
	Mesh(float* vertices, unsigned int vCount, std::string filePath);
	~Mesh();

	void Rotate(float x, float y, float z);
	void Scale(float x, float y, float z);
	void Move(float x, float y, float z);

	void Draw(Shader* program);
};

