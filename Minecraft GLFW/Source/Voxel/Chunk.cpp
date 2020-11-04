#include <fstream>
#include <string>

#include "Chunk.h"
#include "../Mesh/Mesh.h"


Chunk::Chunk(Shader* program) : program(program) {
	for(int i = 0; i < 16; i++) {
		for(int j = 0; j < 16; j++) {
			vox[i][j][0].Set(1);
		}
	}
	for(int i = 1; i < 16; i++) {
		for(int j = 0; j < 16; j++) {
			for(int l = 0; l < 16; l++) {
				vox[l][j][i].Set(0);
			}
		}
	}
}

Chunk::~Chunk() {
}

void Chunk::DrawVox(unsigned int x, unsigned int y, unsigned int z) {
	Voxel::Draw draw(program, x, y, z);
	if(x > 0 & vox[x - 1][y][z].Get() != 0) {
		draw.XBack();
	}
	if(x < 16 & vox[x + 1][y][z].Get() != 0) {
		draw.XFront();
	}
	if(y > 0 & vox[x][y - 1][z].Get() != 0) {
		draw.YBack();
	}
	if(y < 1 & vox[x][y + 1][z].Get() != 0) {
		draw.YFront();
	}
	if(z > 0 & vox[x][y][z - 1].Get() != 0) {
		draw.ZBack();
	}
	if(z < 16 & vox[x][y][z + 1].Get() != 0) {
		draw.YFront();
	}
}

void Chunk::Draw() {
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			for(int l = 0; l < 4; l++) {
				if(vox[i][j][l].Get() != 0) {
					DrawVox(i, j, l);
				}
			}
		}
	}
}
