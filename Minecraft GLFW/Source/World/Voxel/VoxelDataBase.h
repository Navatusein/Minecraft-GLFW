#pragma once

#include <array>
#include <memory>

#include "../../Utility/Singleton.h"

#include"VoxelData.h"

class VoxelDataBase : public Singleton {
private:
	VoxelData* Voxels = new VoxelData[(unsigned)BlocksID::DataType];
public:
	VoxelDataBase();

	~VoxelDataBase();

	const VoxelData& getVoxel(BlocksID id);
	const BlockData& getVoxelData(BlocksID id);
};

