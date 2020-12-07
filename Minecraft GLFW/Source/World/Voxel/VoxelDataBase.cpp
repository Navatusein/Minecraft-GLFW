#include "VoxelDataBase.h"



VoxelDataBase::VoxelDataBase() {
	Voxels[(unsigned short)BlocksID::Air].ReadFile("Air");
}

VoxelDataBase::~VoxelDataBase() {
	delete[] Voxels;
}

const VoxelData& VoxelDataBase::getVoxel(BlocksID id) {
	return Voxels[(unsigned short)id];
}

const BlockData& VoxelDataBase::getVoxelData(BlocksID id) {
	return Voxels[(unsigned short)id].getData();
}
