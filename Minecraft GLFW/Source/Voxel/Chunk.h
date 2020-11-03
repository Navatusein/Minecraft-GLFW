#pragma once
#include "Voxel.h"
class Chunk
{
private:
	Voxel vox[16][16][16];
public:
	Chunk();
	~Chunk();

	void Draw();
};

