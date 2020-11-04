#pragma once
#include "Voxel.h"
#include "../Graphic/Shader.h"
class Chunk
{
private:
	Voxel vox[16][16][16];
	Shader* program;
	void DrawVox(unsigned int x, unsigned int y, unsigned int z);
public:
	Chunk(Shader* program);
	~Chunk();

	void Draw();
};

