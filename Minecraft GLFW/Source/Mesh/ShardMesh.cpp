#include "ShardMesh.h"

ShardMesh::ShardMesh(BigMesh* parent) : parent(parent) {
}

ShardMesh::~ShardMesh() {
}

void ShardMesh::Push(float* plane, int x, int y, int z) {

	for(int i = 0; i < 6; i++) {
		plane[i * 5] += x;
		plane[i * 5 + 1] += y;
		plane[i * 5 + 2] += z;
	}

	parent->Push(plane, 6);
	
}

void ShardMesh::PushTop(int x, int y, int z) {
	float plane[] = {
		// x    y     z     u     v
	   0.f, 1.f, 1.f, 0.f, 1.f,
	   1.f, 1.f, 1.f, 1.f, 1.f,
	   0.f, 1.f, 0.f, 0.f, 0.f,

	   1.f, 1.f, 0.f, 1.f, 0.f,
	   0.f, 1.f, 0.f, 0.f, 0.f,
	   1.f, 1.f, 1.f, 1.f, 1.f,
	};

	Push(plane, x, y, z);

}

void ShardMesh::PushBottom(int x, int y, int z) {

	float plane[] = {
		// x    y     z     u     v
	   0.f, 0.f, 0.f, 0.f, 0.f,
       1.f, 0.f, 0.f, 1.f, 0.f,
       0.f, 0.f, 1.f, 0.f, 1.f,
       
       1.f, 0.f, 0.f, 1.f, 0.f,
       1.f, 0.f, 1.f, 1.f, 1.f,
       0.f, 0.f, 1.f, 0.f, 1.f,
	};
	Push(plane, x, y, z);
}

void ShardMesh::PushXFront(int x, int y, int z) {
	float plane[] = {
		// x    y     z     u     v
		0.f, 0.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 1.f, 0.f,
		1.f, 0.f, 0.f, 0.f, 1.f,
					
		0.f, 1.f, 0.f, 1.f, 0.f,
		1.f, 1.f, 0.f, 1.f, 1.f,
		1.f, 0.f, 0.f, 0.f, 1.f,
	};
	Push(plane, x, y, z);
}

void ShardMesh::PushXRear(int x, int y, int z) {
	float plane[] = {
		1.f, 0.f, 1.f, 0.f, 1.f,
		1.f, 1.f, 1.f, 1.f, 1.f,
		0.f, 0.f, 1.f, 0.f, 0.f,
					
		0.f, 1.f, 1.f, 1.f, 0.f,
		0.f, 0.f, 1.f, 0.f, 0.f,
		1.f, 1.f, 1.f, 1.f, 1.f,
	};
	Push(plane, x, y, z);
}

void ShardMesh::PushZFront(int x, int y, int z) {
	float plane[] = {
		1.f, 0.f, 0.f, 0.f, 0.f,
		1.f, 1.f, 0.f, 1.f, 0.f,
		1.f, 0.f, 1.f, 0.f, 1.f,

		1.f, 1.f, 0.f, 1.f, 0.f,
		1.f, 1.f, 1.f, 1.f, 1.f,
		1.f, 0.f, 1.f, 0.f, 1.f,
	};
	Push(plane, x, y, z);
}

void ShardMesh::PushZRear(int x, int y, int z) {
	float plane[] = {
		0.f, 0.f, 1.f, 0.f, 1.f,
		0.f, 1.f, 1.f, 1.f, 1.f,
		0.f, 0.f, 0.f, 0.f, 0.f,

		0.f, 1.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 1.f, 1.f, 1.f,
	};
	Push(plane, x, y, z);
}
