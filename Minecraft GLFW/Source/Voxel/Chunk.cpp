#include <fstream>
#include <string>

#include "Chunk.h"
#include "../Mesh/Mesh.h"


Chunk::Chunk(Texture* textureAtlas) {
	mesh.Construct(CHUNK_X * CHUNK_Y * CHUNK_Z * 4 * 6, CHUNK_X * CHUNK_Y * CHUNK_Z * 6 * 6, textureAtlas);
	shard.Construct(&mesh);

	vox = new Voxel** [CHUNK_X];
	for(int x = 0; x < CHUNK_X; x++) {
		vox[x] = new Voxel * [CHUNK_Y];
		for(int y = 0; y < CHUNK_Y; y++) {
			vox[x][y] = new Voxel[CHUNK_Z];
			for(int z = 0; z < CHUNK_Z; z++) {
				vox[x][y][z].Set(0);
			}
		}
	}

}

Chunk::~Chunk() {
	for(int x = 0; x < CHUNK_X; x++) {
		for(int y = 0; y < CHUNK_Y; y++) {
			delete[]vox[x][y];
		}
		delete[]vox[x];
	}
	delete[]vox;
}

void Chunk::DrawVox(postype x, postype y, postype z) {
	if(y + 1 < CHUNK_Y) {
		if(vox[x][y + 1][z].GetID() == 0) {
			shard.PushTop(vox[x][y][z].GetRef(), x, y, z);
		}
	}
	else {
		//TODO
		shard.PushTop(vox[x][y][z].GetRef(), x, y, z);
	}

	if(y > 0) {
		if(vox[x][y - 1][z].GetID() == 0) {
			shard.PushBottom(vox[x][y][z].GetRef(), x, y, z);
		}
	}
	else {
		//TODO
		shard.PushBottom(vox[x][y][z].GetRef(), x, y, z);
	}

	if(x + 1 < CHUNK_X) {
		if(vox[x + 1][y][z].GetID() == 0) {
			shard.PushXFront(vox[x][y][z].GetRef(), x, y, z);
		}
	}
	else {
		//TODO
		shard.PushXFront(vox[x][y][z].GetRef(), x, y, z);
	}

	if(x > 0) {

		if(vox[x - 1][y][z].GetID() == 0) {
			shard.PushXRear(vox[x][y][z].GetRef(), x, y, z);
		}
	}
	else {
		//TODO
		shard.PushXRear(vox[x][y][z].GetRef(), x, y, z);
	}

	if(z + 1 < CHUNK_Z) {
		if(vox[x][y][z + 1].GetID() == 0) {
			shard.PushZFront(vox[x][y][z].GetRef(), x, y, z);
		}
	}
	else {
		//TODO
		shard.PushZFront(vox[x][y][z].GetRef(), x, y, z);
	}

	if(z > 0) {

		if(vox[x][y][z - 1].GetID() == 0) {
			shard.PushZRear(vox[x][y][z].GetRef(), x, y, z);
		}
	}
	else {
		//TODO
		shard.PushZRear(vox[x][y][z].GetRef(), x, y, z);
	}


}

void Chunk::Update() {
	mesh.Clear();

	for(postype x = 0; x < CHUNK_X; x++) {
		for(postype y = 0; y < CHUNK_Y; y++) {
			for(postype z = 0; z < CHUNK_Z; z++) {
				if(vox[x][y][z].GetID() != 0) {
					DrawVox(x, y, z);
				}
			}
		}
	}

	mesh.UpdateMesh();
}

void Chunk::Draw(Shader* program) {
	mesh.Draw(program);
}

void Chunk::Fill() {
	for(postype x = 0; x < CHUNK_X; x++) {
		for(postype y = 0; y < CHUNK_Y; y++) {
			for(postype z = 0; z < CHUNK_Z; z++) {
				if(y == 5) {
					vox[x][y][z].Set(1);
				}
				else if(y < 5){
					vox[x][y][z].Set(3);
				}
				else {
					vox[x][y][z].Set(0);
				}
			}
		}
	}
}
