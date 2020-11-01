#include "Mesh.h"
#include <iostream>

Mesh::Mesh(float* vertices, unsigned int vCount, std::string filePath) : vCount(vCount){
	VBO.Construct(vertices, vCount);
	VAO.AddBuffer(VBO);
	
	VAO.Unbind();
	VBO.Unbind();

	texture = CreateTexture(filePath);
}

Mesh::~Mesh() {
}

void Mesh::Draw() {
	VAO.Bind();
	texture->Bind();
	glDrawArrays(GL_TRIANGLES, 0, vCount);
	texture->Unbind();
	VAO.Unbind();
}
