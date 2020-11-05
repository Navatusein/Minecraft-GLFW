#pragma once

#include <stdlib.h>

#include "../ErrorHandling.h"
#include "../Mesh/Mesh.h"
#include "../Voxel/Chunk.h"
#include "../Voxel/Voxel.h"

class VoxelRenderer {
	float* Buffer;
	size_t Capacity;
public:
	VoxelRenderer(size_t capacity);
	~VoxelRenderer();

	Mesh* Render(Chunk* chunk, const Chunk** chunks);
};


