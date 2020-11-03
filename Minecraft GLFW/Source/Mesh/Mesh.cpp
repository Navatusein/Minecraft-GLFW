#include "Mesh.h"

Mesh::Mesh(float* vertices, unsigned int vCount, Texture* tex) : vCount(vCount){
	VBO.Construct(vertices, vCount);
	VAO.AddBuffer(VBO);
	VAO.Unbind();
	VBO.Unbind();
	transform = glm::mat4(1.f);
	texture = tex;
}

Mesh::~Mesh() {
}

void Mesh::Rotate(float x, float y, float z) {
	transform = glm::rotate(transform, x * (float)57.2958, glm::vec3(1, 0, 0));
	transform = glm::rotate(transform, y * (float)57.2958, glm::vec3(0, 1, 0));
	transform = glm::rotate(transform, z * (float)57.2958, glm::vec3(0, 0, 1));
}

void Mesh::Scale(float x, float y, float z) {
	transform = glm::scale(transform,  glm::vec3(x, y, z));
}

void Mesh::Move(float x, float y, float z) {
	transform = glm::translate(transform, glm::vec3(x, y, z));
}

void Mesh::Draw(Shader* program) {
	VAO.Bind();
	texture->Bind();
	program->Bind();

	program->UniformMatrix("transform", transform);
	glDrawArrays(GL_TRIANGLES, 0, vCount);

	program->Unbind();
	texture->Unbind();
	VAO.Unbind();
}
