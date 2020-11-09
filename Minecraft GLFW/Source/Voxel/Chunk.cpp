#include <fstream>
#include <string>

#include "Chunk.h"
#include "../Mesh/Mesh.h"

Chunk::Chunk() {
}

Chunk::Chunk(const Chunk& val) : vox(val.vox), mesh(val.mesh), shard(val.shard), pos(val.pos) {
}

Chunk::Chunk(Texture* textureAtlas, int posx, int posy, int posz){
	mesh.Construct(CHUNK_X * CHUNK_Y * CHUNK_Z * 4 * 6, CHUNK_X * CHUNK_Y * CHUNK_Z * 6 * 6, textureAtlas);
	shard.Construct(&mesh);

	pos.x = posx;
	pos.y = posy;
	pos.z = posz;

	vox = new Voxel * *[CHUNK_X];
	for(int x = 0; x < CHUNK_X; x++) {
		vox[x] = new Voxel * [CHUNK_Y];
		for(int y = 0; y < CHUNK_Y; y++) {
			vox[x][y] = new Voxel[CHUNK_Z];
			for(int z = 0; z < CHUNK_Z; z++) {
				vox[x][y][z].Set(0);
			}
		}
	}

	mesh.Move(posx*CHUNK_X, posy*CHUNK_Y, posz*CHUNK_Z);
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

void Chunk::DrawVox(postype x, postype y, postype z, Chunk* neighbour[6]) {

	if(y + 1 < CHUNK_Y) {
		if(vox[x][y + 1][z].GetID() == 0) {
			shard.PushTop(vox[x][y][z].GetRef(), x, y, z);
		}
	}
	else {
		shard.PushTop(vox[x][y][z].GetRef(), x, y, z);
		/*
		if(nTop != nullptr) {
			//TODO
		}
		*/
	}

	if(y > 0) {
		if(vox[x][y - 1][z].GetID() == 0) {
			shard.PushBottom(vox[x][y][z].GetRef(), x, y, z);
		}
	}
	else {
		shard.PushBottom(vox[x][y][z].GetRef(), x, y, z);
		/*
		if(nBottom != nullptr) {
			//TODO
		}
		*/
	}

	if(x + 1 < CHUNK_X) {
		if(vox[x + 1][y][z].GetID() == 0) {
			shard.PushXFront(vox[x][y][z].GetRef(), x, y, z);
		}
	}
	else {
		if(neighbour[0]) {
			if(neighbour[0]->vox[0][y][z].GetID() == 0) {
				shard.PushXFront(vox[x][y][z].GetRef(), x, y, z);
			}
		}
	}

	if(x > 0) {
		if(vox[x - 1][y][z].GetID() == 0) {
			shard.PushXRear(vox[x][y][z].GetRef(), x, y, z);
			
		}
	}
	else {
		if(neighbour[1]) {
			if(neighbour[1]->vox[CHUNK_X - 1][y][z].GetID() == 0) {
				shard.PushXRear(vox[x][y][z].GetRef(), x, y, z);
			}
		}
	}

	if(z + 1 < CHUNK_Z) {
		if(vox[x][y][z + 1].GetID() == 0) {
			shard.PushZFront(vox[x][y][z].GetRef(), x, y, z);
		}
	}
	else {
		if(neighbour[2]) {
			if(neighbour[2]->vox[x][y][0].GetID() == 0) {
				shard.PushZFront(vox[x][y][z].GetRef(), x, y, z);
			}
		}
	}

	if(z > 0) {

		if(vox[x][y][z - 1].GetID() == 0) {
			shard.PushZRear(vox[x][y][z].GetRef(), x, y, z);
		}
	}
	else {
		if(neighbour[3]) {
			if(neighbour[3]->vox[x][y][CHUNK_Z - 1].GetID() == 0) {
				shard.PushZRear(vox[x][y][z].GetRef(), x, y, z);
			}
		}
	}


}

void Chunk::Update(Chunk* neighbour[6]) {
	mesh.Clear();
	for(postype x = 0; x < CHUNK_X; x++) {
		for(postype y = 0; y < CHUNK_Y; y++) {
			for(postype z = 0; z < CHUNK_Z; z++) {
				if(vox[x][y][z].GetID() != 0) {
					DrawVox(x, y, z, neighbour);
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


	//temporary, delete it later 
	vox[1][5][1].Set(3);
	vox[1][5][2].Set(3);
	vox[2][5][2].Set(3);
	vox[1][5][3].Set(3);
}

void Chunk::Setblock(unsigned short int id, postype x, postype y, postype z) {
	if(x < CHUNK_X && y < CHUNK_Y && x < CHUNK_Z && x > 0 && y > 0 && x > 0) {
		vox[x][y][z].Set(id);
	}
}

Voxel* Chunk::Getblock(postype x, postype y, postype z) {
	if(this) {
		if(x > 0 && x < CHUNK_X && y > 0 && y < CHUNK_Y && z > 0 && z < CHUNK_Z) {
			return vox[x][y][z].GetRef();
		}
		else return nullptr;
	}
	else return nullptr;
}

glm::vec3 Chunk::GetPos() {
	return pos;
}
