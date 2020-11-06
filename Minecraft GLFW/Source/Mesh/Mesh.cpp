#include "Mesh.h"

Mesh::Mesh() {
}

Mesh::Mesh(float* vertices, unsigned int* indices, unsigned int vCount, Texture* tex) : vCount(vCount){
	VAO.Bind();
	VBO.Construct(vertices, vCount);
	IBO.Construct(indices, vCount);
	VAO.AddBuffer(VBO);
	VAO.Unbind();
	VBO.Unbind();
	transform = glm::mat4(1.f);
	texture = tex;
}

Mesh::~Mesh() {
}

void Mesh::Construct(float* vertices, unsigned int* indices, unsigned int vCount, Texture* tex) {
	this->vCount = vCount;
	VAO.Bind();
	VBO.Construct(vertices, vCount);
	IBO.Construct(indices, vCount);
	VAO.AddBuffer(VBO);
	VAO.Unbind();
	VBO.Unbind();
	transform = glm::mat4(1.f);
	texture = tex;
}

void Mesh::Rotate(float x, float y, float z) {
	transform = glm::rotate(transform, x* (float)0.0174533, glm::vec3(1.f, 0, 0));
	transform = glm::rotate(transform, y * (float)0.0174533, glm::vec3(0, 1.f, 0));
	transform = glm::rotate(transform, z * (float)0.0174533, glm::vec3(0, 0, 1.f));
}



void Mesh::Scale(float x, float y, float z) {
	transform = glm::scale(transform,  glm::vec3(x, y, z));
}

void Mesh::Move(float x, float y, float z) {
	transform = glm::translate(transform, glm::vec3(x, y, z));
}

void Mesh::Center() {
	transform = glm::mat4(1.f);
}

void Mesh::Draw(Shader* program) {
	VAO.Bind();
	IBO.Bind();
	texture->Bind();
	program->Bind();

	program->UniformMatrix("transform", transform);

	glDrawElements(GL_TRIANGLES, vCount, GL_UNSIGNED_INT, nullptr);

	program->Unbind();
	texture->Unbind();
	VAO.Unbind();
	IBO.Unbind();
}
