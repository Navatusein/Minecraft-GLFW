#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "BigMesh.h"
#include "../Voxel/Voxel.h"

class ShardMesh
{
private:
	BigMesh* parent;
public:
	ShardMesh();
	ShardMesh(BigMesh* parent);
	~ShardMesh();

	void Construct(BigMesh* parent);

	void Push(float* plane, unsigned int* indices, postype x, postype y, postype z);

	void PushTop(Voxel* vox, postype x, postype y, postype z);
	void PushBottom(Voxel* vox, postype x, postype y, postype z);
	void PushXFront(Voxel* vox, postype x, postype y, postype z);
	void PushXRear(Voxel* vox, postype x, postype y, postype z);
	void PushZFront(Voxel* vox, postype x, postype y, postype z);
	void PushZRear(Voxel* vox, postype x, postype y, postype z);
};