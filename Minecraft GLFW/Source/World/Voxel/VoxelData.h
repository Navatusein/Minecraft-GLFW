#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "../Minecraft GLFW/Source/ErrorHandling.h"

#include "VoxelsID.h"

enum class BlockTypes {
	Block = 0,
	Flora = 1,
	Liguid = 2,
};

struct SideTexture {
	unsigned short Tbegin;
	unsigned char Tcount;
};

struct BlockData {
	BlocksID ID;
	BlockTypes BlockType;
	SideTexture* textures;

	bool isOpaque;
	bool isCollidable;
};

class VoxelData {
private:
	BlockData Data;
public:
	VoxelData(std::string file);

	const BlockData& getData();

	~VoxelData();
};

