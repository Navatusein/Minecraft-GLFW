#pragma once
#include <GL/glew.h>
#include <stdlib.h>

class Mesh {
	unsigned int vao;
	unsigned int vbo;
	size_t vertices;
public:
	Mesh(const float* buffer, size_t vertices, const int* attrs);
	~Mesh();

	void draw(unsigned int primitive);
};

