#pragma once

#include <ctime>
#include <random>

#include "../Graphic/Shader.h"
#include "../Mesh/Mesh.h"
#include "../Graphic/Texture.h"

#define maxID 4;

struct textureVariant
{
private:
	bool Top[2];
	bool Bottom[2];
	bool XFront[2];
	bool XRear[2];
	bool ZFront[2];
	bool ZRear[2];
public:
	unsigned short int getTop() {
		return (unsigned short int)1 * Top[0] + (unsigned short int)2 * Top[1];
	}
	unsigned short int getBottom() {
		return (unsigned short int)1 * Bottom[0] + (unsigned short int)2 * Bottom[1];
	}
	unsigned short int getXFront() {
		return (unsigned short int)1 * XFront[0] + (unsigned short int)2 * XFront[1];
	}
	unsigned short int getXRear() {
		return (unsigned short int)1 * XRear[0] + (unsigned short int)2 * XRear[1];
	}
	unsigned short int getZFront() {
		return (unsigned short int)1 * ZFront[0] + (unsigned short int)2 * ZFront[1];
	}
	unsigned short int getZRear() {
		return (unsigned short int)1 * ZRear[0] + (unsigned short int)2 * ZRear[1];
	}

	void randomize() {
		unsigned short int seed = rand() % 4096;
		Top[0] = seed % 2;
		seed /= 2;
		Top[1] = seed % 2;
		seed /= 2;
		Bottom[0] = seed % 2;
		seed /= 2;
		Bottom[1] = seed % 2;
		seed /= 2;
		XFront[0] = seed % 2;
		seed /= 2;
		XFront[1] = seed % 2;
		seed /= 2;
		XRear[0] = seed % 2;
		seed /= 2;
		XRear[1] = seed % 2;
		seed /= 2;
		ZFront[0] = seed % 2;
		seed /= 2;
		ZFront[1] = seed % 2;
		seed /= 2;
		ZRear[0] = seed % 2;
		seed /= 2;
		ZRear[1] = seed % 2;
	}
};


struct Voxel
{
private:
	unsigned short int id;
	textureVariant tVar;
public:
	Voxel();
	Voxel(unsigned short id);
	~Voxel();

	void Set(unsigned short int id);
	void Set(unsigned short int id, textureVariant texVar);

	unsigned short int GetID();

	textureVariant* Get_tVar();

	Voxel* GetRef();
};