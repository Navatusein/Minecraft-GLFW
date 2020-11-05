#pragma once
#include "Voxel.h"
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>

#define ChunkW 16
#define ChunkH 256
#define ChunkD 16
#define ChunkVol (ChunkW * ChunkH * ChunkD)

class Chunk {
public:
	int x, y, z;
	Voxel* Voxels;
	bool Modified = true;
	Chunk(int x, int y, int z);
	~Chunk();
};

