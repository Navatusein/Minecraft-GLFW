#include "VoxelDataBase.h"

#define MaxID 4

VoxelDataBase::VoxelDataBase() {
	Voxels[(int)BlocksID::Air].ReadFile("Air");
}

const VoxelData& VoxelDataBase::getVoxel(BlocksID id) {
	return Voxels[(int)id];
}

const BlockData& VoxelDataBase::getVoxelData(BlocksID id) {
	return Voxels[(int)id].getData();
}
