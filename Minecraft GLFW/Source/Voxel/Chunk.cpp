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
			//float height = glm::perlin(glm::vec3(real_x*0.0026125f,real_z*0.0026125f, 0.0f));
			//height += glm::perlin(glm::vec3(real_x*0.006125f,real_z*0.006125f, 0.0f))*0.5f;
			for (int y = 0; y < ChunkH; y++) {
				int real_y = y + this->y * ChunkH;
				int id = glm::perlin(glm::vec3(real_x * 0.0125f, real_y * 0.0125f, real_z * 0.0125f)) > 0.1f;//real_y <= (height) * 60 + 30;
				if (real_y <= 2)
					id = 2;
				Voxels[(y * ChunkD + z) * ChunkW + x].id = id;
			}
		}
	}
}

Chunk::~Chunk() {
	delete[] Voxels;
}

