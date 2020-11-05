#include "Voxel.h"

Voxel::Voxel() {
}

Voxel::~Voxel() {
}

void Voxel::Set(int id) {
	this->id = id;
}

int Voxel::Get() {
	return id;
}
