#include "BigMesh.h"
#include "glm/glm.hpp"

BigMesh::BigMesh(Texture* tex) {
	textureAtlas = tex;
}

BigMesh::~BigMesh() {
}

void BigMesh::Draw(Shader* program) {
	textureAtlas->Bind();
	program->Bind();
	VAO.Bind();

	program->UniformMatrix("transform", glm::mat4(1.f));
	glDrawArrays(GL_TRIANGLES, 0, vertexArr.size());

	program->Unbind();
	textureAtlas->Unbind();
	VAO.Unbind();
}

void BigMesh::Update() {
	VBO.Delete();
	VBO.Construct(vertexArr.data(), vertexArr.size() / 5);
	VAO.AddBuffer(VBO);
	VAO.Unbind();
	VBO.Unbind();
}

void BigMesh::Clear() {
	vertexArr.clear();
}



void BigMesh::Push(float* vertices, unsigned int vCount) {
	for(int i = 0; i < vCount*5; i++) {
		vertexArr.push_back(vertices[i]);
	}
}
