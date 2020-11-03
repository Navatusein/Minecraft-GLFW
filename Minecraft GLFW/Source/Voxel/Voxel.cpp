#include "Voxel.h"

Voxel::Voxel() {
	id = 0;
}

Voxel::~Voxel() {
}

void Voxel::Set(int id) {
	this->id = id;
}

int Voxel::Get() {
	return id;
}
