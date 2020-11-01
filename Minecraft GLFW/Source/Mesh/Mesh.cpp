#include "Mesh.h"
#include <iostream>

Mesh::Mesh(float* vertices, unsigned int vCount) : vCount(vCount){
	VBO.Construct(vertices, vCount);
	VAO.AddBuffer(VBO);
	
	VAO.Unbind();
	VBO.Unbind();
}

Mesh::~Mesh() {
}

void Mesh::Draw() {
	VAO.Bind();
	
	glDrawArrays(GL_TRIANGLES, 0, vCount);
	VAO.Unbind();
}
