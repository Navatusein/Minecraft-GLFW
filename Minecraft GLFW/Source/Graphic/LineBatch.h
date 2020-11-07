#pragma once

#include "../Mesh/Mesh.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class LineBatch {
	Mesh* mesh;
	float* buffer;
	size_t index;
	size_t capacity;
public:
	LineBatch(size_t capacity);
	~LineBatch();

	void Line(float x1, float y1, float z1, float x2, float y2, float z2, float r, float g, float b, float a);
	void Box(float x, float y, float z, float w, float h, float d,float r, float g, float b, float a);

	void Render();
};
