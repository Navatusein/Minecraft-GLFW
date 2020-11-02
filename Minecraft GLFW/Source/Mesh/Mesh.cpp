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
	transform = glm::rotate(transform, 0.0174533f, glm::vec3(x, y, z));
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
