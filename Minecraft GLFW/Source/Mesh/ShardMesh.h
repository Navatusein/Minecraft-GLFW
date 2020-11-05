#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "BigMesh.h"

class ShardMesh
{
private:
	BigMesh* parent;
public:
	ShardMesh(BigMesh* parent);
	~ShardMesh();

	void Push(float* plane, unsigned int* indices, int x, int y, int z);

	void PushTop(int x, int y, int z);
	void PushBottom(int x, int y, int z);
	void PushXFront(int x, int y, int z);
	void PushXRear(int x, int y, int z);
	void PushZFront(int x, int y, int z);
	void PushZRear(int x, int y, int z);
};