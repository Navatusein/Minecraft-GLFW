#pragma once

#include <stdlib.h>

#include "../ErrorHandling.h"
#include "../Mesh/Mesh.h"
#include "../Voxel/Chunk.h"
#include "../Voxel/Voxel.h"

class VoxelRenderer {
	float* buffer;
	size_t capacity;
public:
	VoxelRenderer(size_t capacity);
	~VoxelRenderer();

	Mesh* render(Chunk* chunk, const Chunk** chunks);
};


