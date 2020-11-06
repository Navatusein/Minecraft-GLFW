#include <glm/glm.hpp>

#include "BigMesh.h"

#include "../ErrorHandling.h"

BigMesh::BigMesh() {
}

BigMesh::BigMesh(unsigned int max_vCount, unsigned int max_eCount, Texture* tex) : max_vCount(vCount), max_eCount(max_eCount), vCount(0), eCount(0) {
	textureAtlas = tex;
	vertexArr = new float[max_vCount * 5];
	indexArr = new unsigned int[max_eCount];
	transform = glm::mat4(1.f);
}

BigMesh::~BigMesh() {
	delete[]vertexArr;
	delete[]indexArr;
}

void BigMesh::Construct(unsigned int max_vCount, unsigned int max_eCount, Texture* tex) {
	transform = glm::mat4(1.f);
	textureAtlas = tex;
	vertexArr = new float[max_vCount * 5];
	indexArr = new unsigned int[max_eCount];

	this->max_vCount = max_vCount;
	this->max_eCount = max_eCount;
	vCount = 0;
	eCount = 0;
}

void BigMesh::Draw(Shader* program) {
	textureAtlas->Bind();
	program->Bind();
	VAO.Bind();
	IBO.Bind();

	program->UniformMatrix("transform", transform);

	GLCall(glDrawElements(GL_TRIANGLES, eCount, GL_UNSIGNED_INT, 0));

	program->Unbind();
	textureAtlas->Unbind();
	IBO.Unbind();
	VAO.Unbind();
}

void BigMesh::UpdateMesh() {
	VBO.Delete();

	VBO.Construct(vertexArr, vCount);
	IBO.Construct(indexArr, eCount);
	VAO.AddBuffer(VBO);

	VAO.Unbind();
	VBO.Unbind();
	IBO.Unbind();
}

void BigMesh::Clear() {
	delete[]vertexArr;
	delete[]indexArr;

	vertexArr = new float[max_vCount * 5];
	indexArr = new unsigned int[max_eCount];

	vCount = 0;
	eCount = 0;
}

void BigMesh::Move(float x, float y, float z) {
	transform = glm::translate(transform, glm::vec3(x, y, z));
}

void BigMesh::Center() {
	transform = glm::mat4(1.f);
}



void BigMesh::Push(float* vertices, unsigned int add_vCount, unsigned int* indices, unsigned int add_eCount) {

	for(int i = 0; i < add_vCount*5; i++) {
		vertexArr[vCount*5+i] = vertices[i];
	}

	for(int i = 0; i < add_eCount; i++) {
		indexArr[eCount+i] = indices[i] + vCount;
	}

	vCount += add_vCount;
	eCount += add_eCount;
}
