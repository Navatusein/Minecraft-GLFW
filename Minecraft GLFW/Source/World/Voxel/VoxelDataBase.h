#pragma once

#include <array>
#include <memory>

#include "../../Utility/Singleton.h"

#include"VoxelData.h"

class VoxelDataBase : public Singleton {
private:
	std::array<std::unique_ptr<VoxelData>,(unsigned)BlocksID::DataType> Voxels;
public:
	VoxelDataBase();

	const VoxelData& getVoxel(BlocksID id);
	const BlockData& getVoxelData(BlocksID id);
};

