#include <fstream>
#include <string>

#include "Chunk.h"
#include "../Mesh/Mesh.h"


Chunk::Chunk(int xpos, int ypos, int zpos) : x(xpos), y(ypos), z(zpos) {
	Voxels = new Voxel[ChunkVol];

	for (int z = 0; z < ChunkD; z++) {
		for (int x = 0; x < ChunkW; x++) {
			int real_x = x + this->x * ChunkW;
			int real_z = z + this->z * ChunkD;
			for (int y = 0; y < ChunkH; y++) {
				int real_y = y + this->y * ChunkH;
				int id = 0;
				if (real_y <= 2) {
					id = 2;
				}
				if (real_y == 3) {
					id = 1;
				}
				Voxels[(y * ChunkD + z) * ChunkW + x].id = id;
			}
		}
	}
}

Chunk::~Chunk() {
	delete[] Voxels;
}

