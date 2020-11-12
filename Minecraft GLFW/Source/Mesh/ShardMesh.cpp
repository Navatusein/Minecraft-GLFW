#include "ShardMesh.h"

ShardMesh::ShardMesh() {
}

ShardMesh::ShardMesh(BigMesh* parent) : parent(parent) {
}

ShardMesh::~ShardMesh() {
}

void ShardMesh::Construct(BigMesh* parent) {
	this->parent = parent;
}

void ShardMesh::Push(float* plane, unsigned int* indices, postype x, postype y, postype z) {

    for(int i = 0; i < 4; i++) {
		plane[i * 5] += x;
		plane[i * 5 + 1] += y;
		plane[i * 5 + 2] += z;
	}

	parent->Push(plane, 4, indices, 6);
	
}


void ShardMesh::PushTop(Voxel* vox, postype x, postype y, postype z) {
	
	float u[2];
	float v[2];
	{
		float U = vox->Get_tVar()->getTop();
		float V = vox->GetID();
		if(V > ATLAS_W) {
			return;
		}

		u[0] = U / ATLAS_H;
		u[1] = (U + 1) / ATLAS_H;
		v[0] = (V - 1) / ATLAS_W;
		v[1] = V / ATLAS_W;
	}

	float plane[] = {
		// x    y     z     u     v
	   0.f, 1.f, 0.f, v[0], u[0],
	   1.f, 1.f, 0.f, v[1], u[0],
	   1.f, 1.f, 1.f, v[1], u[1],
	   0.f, 1.f, 1.f, v[0], u[1],
	};
	unsigned int indices[] = {
		0, 2, 1,
		0, 3, 2,
	};
	Push(plane, indices, x, y, z);

}

void ShardMesh::PushBottom(Voxel* vox, postype x, postype y, postype z) {

	float u[2];
	float v[2];
	{
		float U = vox->Get_tVar()->getBottom();
		float V = vox->GetID();
		if(V > ATLAS_W) {
			return;
		}

		if(V == 1) {
			V = 3;
		}

		u[0] = U / ATLAS_H;
		u[1] = (U + 1) / ATLAS_H;

		v[0] = (V - 1) / ATLAS_W;
		v[1] = V / ATLAS_W;
	}

	float plane[] = {
		// x    y     z     u     v
	   0.f, 0.f, 0.f, v[0], u[0],
	   1.f, 0.f, 0.f, v[1], u[0],
	   1.f, 0.f, 1.f, v[1], u[1],
	   0.f, 0.f, 1.f, v[0], u[1],
	};
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3,
	};
	Push(plane, indices, x, y, z);
}

void ShardMesh::PushZFront(Voxel* vox, postype x, postype y, postype z) {
	float u[2];
	float v[2];
	{
		float U = vox->Get_tVar()->getZFront();
		float V = vox->GetID();

		if(V == 1) {
			V = 2;
		}

		u[0] = U / ATLAS_H;
		u[1] = (U + 1) / ATLAS_H;

		v[0] = (V - 1) / ATLAS_W;
		v[1] = V / ATLAS_W;
	}

	float plane[] = {
		// x    y     z     u     v
	   0.f, 0.f, 1.f, v[0], u[0],
	   1.f, 0.f, 1.f, v[1], u[0],
	   1.f, 1.f, 1.f, v[1], u[1],
	   0.f, 1.f, 1.f, v[0], u[1],
	};
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3,
	};
	Push(plane, indices, x, y, z);
}

void ShardMesh::PushZRear(Voxel* vox, postype x, postype y, postype z) {
	float u[2];
	float v[2];
	{
		float U = vox->Get_tVar()->getZRear();
		float V = vox->GetID();

		if(V == 1) {
			V = 2;
		}

		u[0] = U / ATLAS_H;
		u[1] = (U + 1) / ATLAS_H;

		v[0] = (V - 1) / ATLAS_W;
		v[1] = V / ATLAS_W;
	}

	float plane[] = {
		// x    y     z     u     v
	   0.f, 0.f, 0.f, v[0], u[0],
	   1.f, 0.f, 0.f, v[1], u[0],
	   1.f, 1.f, 0.f, v[1], u[1],
	   0.f, 1.f, 0.f, v[0], u[1],
	};
	unsigned int indices[] = {
		0, 2, 1,
		0, 3, 2,
	};
	Push(plane, indices, x, y, z);
}

void ShardMesh::PushXFront(Voxel* vox, postype x, postype y, postype z) {
	float u[2];
	float v[2];
	{
		float U = vox->Get_tVar()->getXFront();
		float V = vox->GetID();

		if(V == 1) {
			V = 2;
		}

		u[0] = U / ATLAS_H;
		u[1] = (U + 1) / ATLAS_H;

		v[0] = (V - 1) / ATLAS_W;
		v[1] = V / ATLAS_W;
	}

	float plane[] = {
		// x    y     z     u     v
	   1.f, 0.f, 0.f, v[0], u[0],
	   1.f, 1.f, 0.f, v[0], u[1],
	   1.f, 1.f, 1.f, v[1], u[1],
	   1.f, 0.f, 1.f, v[1], u[0],
	};
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3,
	};
	Push(plane, indices, x, y, z);
}

void ShardMesh::PushXRear(Voxel* vox, postype x, postype y, postype z) {
	float u[2];
	float v[2];
	{
		float U = vox->Get_tVar()->getXRear();
		float V = vox->GetID();

		if(V == 1) {
			V = 2;
		}

		u[0] = U / ATLAS_H;
		u[1] = (U + 1) / ATLAS_H;

		v[0] = (V - 1) / ATLAS_W;
		v[1] = V / ATLAS_W;
	}

	float plane[] = {
		// x    y     z     u     v
	   0.f, 0.f, 0.f, v[0], u[0],
	   0.f, 1.f, 0.f, v[0], u[1],
	   0.f, 1.f, 1.f, v[1], u[1],
	   0.f, 0.f, 1.f, v[1], u[0],
	};
	unsigned int indices[] = {
		0, 2, 1,
		0, 3, 2,
	};
	Push(plane, indices, x, y, z);
}
