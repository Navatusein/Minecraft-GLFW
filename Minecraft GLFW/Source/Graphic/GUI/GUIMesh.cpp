
#include "GUIMesh.h"
#include "../../ErrorHandling.h"

#include <iostream>

GUIMesh::GUIMesh(Texture* textureAtlas) : textureAtlas(textureAtlas){
}

GUIMesh::~GUIMesh() {
}

void GUIMesh::Draw(Shader* program) {
	textureAtlas->Bind();
	program->Bind();
	VAO.Bind();
	IBO.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, indexArr.size(), GL_UNSIGNED_INT, 0));

	program->Unbind();
	textureAtlas->Unbind();
	IBO.Unbind();
	VAO.Unbind();
}

void GUIMesh::Push(Vertex4<float>* vertices, unsigned int vCount, unsigned int* indices, unsigned int eCount) {
	int temp = vertexArr.size();
	for(int i = 0; i < vCount; i++) {
		vertexArr.push_back(vertices[i]);
	}
	for(int i = 0; i < eCount; i++) {
		indexArr.push_back(indices[i] + temp);
	}
}

void GUIMesh::UpdateMesh() {
	VBO.Delete();

	VBO.Construct((float*)vertexArr.data(), vertexArr.size()*4);
	IBO.Construct(indexArr.data(), indexArr.size());
	VAO.AddBuffer2d(VBO);
	VAO.Unbind();
	VBO.Unbind();
	IBO.Unbind();
}

void GUIMesh::Clear() {
	vertexArr.clear();
	indexArr.clear();
}
