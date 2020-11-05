#include <glm/glm.hpp>

#include "BigMesh.h"

BigMesh::BigMesh(Texture* tex) {
	textureAtlas = tex;
}

BigMesh::~BigMesh() {
}

void BigMesh::Draw(Shader* program) {
	textureAtlas->Bind();
	program->Bind();
	VAO.Bind();
	IBO.Bind();
	program->UniformMatrix("transform", glm::mat4(1.f));

	glDrawElements(GL_TRIANGLES, indicesArr.size(), GL_UNSIGNED_INT, 0);

	program->Unbind();
	textureAtlas->Unbind();
	IBO.Unbind();
	VAO.Unbind();
}

void BigMesh::Update() {
	VBO.Delete();

	VBO.Construct(vertexArr.data(), vertexArr.size() / 5);
	IBO.Construct(indicesArr.data(), indicesArr.size());
	VAO.AddBuffer(VBO);

	VAO.Unbind();
	VBO.Unbind();
	IBO.Unbind();
}

void BigMesh::Clear() {
	vertexArr.clear();
	indicesArr.clear();
}



void BigMesh::Push(float* vertices, unsigned int vCount, unsigned int* indices, unsigned int eCount) {
	unsigned int temp = vertexArr.size()/5;
	for(int i = 0; i < vCount*5; i++) {
		vertexArr.push_back(vertices[i]);
	}
	for(int i = 0; i < eCount; i++) {
		indicesArr.push_back(indices[i] + temp);
	}
}
