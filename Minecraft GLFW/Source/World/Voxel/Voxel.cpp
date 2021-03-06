#include "Voxel.h"


Voxel::Voxel() : id(0){
}
Voxel::Voxel(unsigned short id) : id(id) {
	tVar.randomize();
}

Voxel::~Voxel() {
}

void Voxel::Set(unsigned short int id) {
	this->id = id;

	tVar.randomize();
}

void Voxel::Set(unsigned short int id, textureVariant texVar) {
	this->id = id;
	tVar = texVar;

}

unsigned short int Voxel::GetID() {
	if(this) {
		return id;
	}
}

textureVariant* Voxel::Get_tVar() {
	return &tVar;
}

Voxel* Voxel::GetRef() {
	return this;
}



