#include "VoxelDataBase.h"

#define MaxID 4

VoxelDataBase::VoxelDataBase() {
	Voxels[(int)BlocksID::Air] = std::make_unique<VoxelData>("Air");
}

const VoxelData& VoxelDataBase::getVoxel(BlocksID id) {
	return *Voxels[(int)id];
}

const BlockData& VoxelDataBase::getVoxelData(BlocksID id) {
	return Voxels[(int)id]->getData();
}
