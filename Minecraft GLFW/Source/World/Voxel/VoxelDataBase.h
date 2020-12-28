#pragma once

/*
This module is not used
*/

#include <array>
#include <memory>

#include "../../Utility/Singleton.h"

#include"VoxelData.h"

#define MaxID 4

class VoxelDataBase : public Singleton {
private:
	VoxelData* Voxels = new VoxelData[(unsigned)BlocksID::Count];
public:
	VoxelDataBase();

	~VoxelDataBase();

	const VoxelData& getVoxel(BlocksID id);
	const BlockData& getVoxelData(BlocksID id);
};

